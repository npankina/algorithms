#include "Array.h"

// class Array
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array()
: Array(0)
{}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array(const size_t &n, const T& value, const Alloc &alloc)
: size_(n), capacity_(n + 10), alloc_(alloc)
{
    data_ = AllocTraits::allocate(alloc_, capacity_); // reserved raw memory and attach it to pointer
    if (size_ > 0)
        for (auto i = 0; i < size_; ++i)
            AllocTraits::construct(alloc_, data_ + i, value); // create some objects
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array(const std::initializer_list<value_type> &t, const T& value, const Alloc &alloc)
: size_(t.size() ), capacity_(size_ * 2), alloc_(alloc)
{
    data_ = AllocTraits::allocate(alloc_, capacity_); // reserved raw memory and attach it to pointer
    for (auto i = 0; i < size_; ++i)
        AllocTraits::construct(alloc_, data_ + i, value); // create some objects
    for (const auto &item : t)
        push_back(item);
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array(const Array &rhs) // copy ctor
: size_(rhs.size_), capacity_(rhs.capacity_)
{
    data_ = AllocTraits::allocate(alloc_, capacity_); // reserved raw memory
    for (auto i = 0; i < size_; ++i)
        AllocTraits::construct(alloc_, data_ + i, rhs.data_ + i); // create some objects
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array(Array &&rhs) noexcept // move ctor
: size_(0), capacity_(0), data_(nullptr)
{ // обнуление старого объекта
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
    std::swap(data_, rhs.data_);
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>& Array<T, Alloc>::operator=(const Array &lhs) // copy assign
{
    if (this != &lhs)
    {
        size_ = lhs.size_;
        capacity_ = lhs.capacity_;
        data_.~T(); // TODO is it right?? Shall we call an allocator.destroy method?
        data_ = AllocTraits::allocate(alloc_, capacity_); // reserved raw memory
//        std::copy(lhs.data_, lhs.data_ + size_, data_);

        for (auto i = 0; i < size_; ++i)
            AllocTraits::construct(alloc_, data_ + i, lhs.data_ + i); // create some objects
    }

    return *this;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>& Array<T, Alloc>::operator=(Array &&rhs) noexcept // move assign
{
    if (this != &rhs)
    {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        data_.~T();
        data_ = std::move(rhs.data_);
    }

    return *this;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::~Array() noexcept
{
    // 1. clear all array
    // 2. deallocate memory

    clear();
    AllocTraits::deallocate(alloc_, data_, capacity_);
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::size_type Array<T, Alloc>::size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
bool Array<T, Alloc>::empty() const noexcept
{
    return size_ == 0;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::size_type Array<T, Alloc>::capacity() const noexcept
{
    return capacity_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::clear() noexcept
{
    for (size_t i = 0; i < size_; ++i)
        AllocTraits::destroy(alloc_, data_ + i);
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::push_back(const value_type &rhs)
{
    // 1. check is capacity equal to size
    // 1.2 realloc if TRUE
    // 2. put in last [] new element -> copy ctor
    // 3. increase size

    if (capacity_ == size_)
        realloc(capacity_ * 2);

    data_[size_ - 1] = rhs;
    ++size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::reference Array<T, Alloc>::operator[](size_type index)
{
    if (index >= size_ or index < 0)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::const_reference Array<T, Alloc>::operator[](size_type index) const
{ // TODO нужно ли бросать исключение, если метод не пытается изменить данные, но объявлен как const?
    if (index >= size_ or index < 0)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::pop_back()
{
    // 1. check is array empty -> nothing to pop => do nothing (noexcept) or throw exception
    // 2. destroy object
    // 3. decrease size

    if (size_ == 0)
        throw std::invalid_argument("Error => Attempt to pop empty vector --- [pop_back method]");

    AllocTraits::destroy(alloc_, data_ + (size_ - 1) );
    --size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::realloc(size_type new_capacity)
{
    // 1. Allocate a new block of memory
    // 2. copy / move old elements into new block
    // 3. delete old block

    if (new_capacity < size_)
        return;

    auto *new_block = AllocTraits::allocate(alloc_, new_capacity);

    size_t i = 0;
    try
    {
        for (; i < size_; ++i)
            AllocTraits::construct(alloc_, new_block + i, std::move(data_[i]) ); // перемещение существующих объектов в новый блок памяти
    } catch (...) // предполагаем поймать bad_alloc
    {
        for (size_t j = 0; j < i; ++j)
            AllocTraits::destroy(alloc_, new_block + i); // уничтожение объектов

        AllocTraits::deallocate(alloc_, new_block, new_capacity); // возврат выделенной памяти
        throw; // выбросить исключение дальше лететь по стеку
    }

    for (i = 0; i < size_; ++i) // уничтожение созданных объектов
        AllocTraits::destroy(alloc_, new_block + i);

    AllocTraits::deallocate(alloc_, data_, capacity_); // возврат памяти

    data_ = new_block;
    capacity_ = new_capacity;
}
#if other
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::iterator Array<T, Alloc>::begin() noexcept
{
    return data_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::iterator Array<T, Alloc>::end() noexcept
{
    return data_ + size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::reference Array<T, Alloc>::front() noexcept
{ // TODO как можно улучшить?? Дублирование кода происходит < front() const noexcept >
    return data_[0];
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::const_reference Array<T, Alloc>::front() const noexcept
{
    return data_[0];
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::reference Array<T, Alloc>::back() noexcept
{
    return data_[size_ - 1];
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::const_reference Array<T, Alloc>::back() const noexcept
{
    return data_[size_ - 1];
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::push_front(const value_type &rhs)
{
    // 1. check is array empty -> push_back
    // 2. check is capacity equal to size -> realloc if TRUE
    // 3. shift (std::move) elements from begin
    // 4. put new data [] -> copy ctor
    // 5. increase size

    if (size_ == 0)
        push_back(rhs);
    else
    {
        if (size_ == capacity_)
            realloc(capacity_ * 2);

        for (size_t i = size_; i > 0; i--)
            data_[i] = std::move(data_[i - 1]);

        data_[0] = rhs;
        ++size_;
    }
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::pop_front() noexcept
{
    // 1. check is array empty -> if TRUE nothing to pop
    // 2. destroy first element
    // 3. shift (std::move) elements to left
    // 4. decrease size

    if (size_ == 0) /* throw std::invalid_argument("Error => the array is empty --- [pop_front method]"); */
        return; // метод аннотирован noexcept

    AllocTraits::destroy(alloc_, data_); // data[0]
    for (int i = 0; i < size_-1; i++)
        data_[i] = std::move(data_[i + 1]);
    --size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::Insert(size_type index, value_type &&value)
{
    // 1. check is index correct
    // 2. check is size equal capacity -> if TRUE realloc
    // 3. shift elements to right
    // 4. insert [] data
    // 5. increase size

    if ( (index < 0) or (index > size_) )
        throw std::out_of_range("Index out of range --- [insert method]");

    if (size_ == capacity_)
        realloc(size_ * 2);

    for (int i = size_; i >= index; --i)
        data_[i + 1] = std::move(data_[i]);

    data_[index] = value;
    ++size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::insert(iterator it, value_type &&value)
{
    // TODO сделать

}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::erase(size_type index)
{
    // 1. check is index correct
    // 2. call dtor for index to erase it
    // 3. shift (std::move) to the left all elements
    // 4. decrease size

    assert(index < 0 or index >= size_);
    if (index < 0 or index >= size_)
        throw std::out_of_range("Index out of range --- [erase method]");

    AllocTraits::destroy(alloc_, data_ + index);
    for (int i = index; i < (size_ - 1); ++i)
        data_[i] = std::move(data_[i + 1]);
    --size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::erase(iterator it)
{

}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::swap(Array &rhs)
{
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
}
//----------------------------------------------------------------------
#endif