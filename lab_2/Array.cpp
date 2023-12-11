#include "Array.h"

// class Array
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array()
: size_(0), capacity_(10)
{}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array(const size_t &n, const T& value, const Alloc &alloc)
: size_(n), capacity_(n + 10), alloc_(alloc)
{
    data_ = AllocTraits::allocate(alloc_, size_);
    for (auto i = 0; i < size_; ++i)
        data_[i] = value;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array(const std::initializer_list<value_type> &t)
: size_(t.size() ), capacity_(size_ * 2), data_(new value_type[capacity_])
// TODO ?? потенциальная ошибка при выделении памяти. Как поведет себя программа, если память выделиться не сможет?
{
    for (auto i : t)
        push_back(i);
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::Array(const Array &lhs) // copy ctor
: size_(lhs.size_), capacity_(lhs.capacity_), data_(new value_type[capacity_])
{
    std::copy(lhs.data_, lhs.data_ + size_, data_);
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
        data_.~T();
        data_ = new value_type[capacity_];
        std::copy(lhs.data_, lhs.data_ + size_, data_);
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
    delete [] data_;
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
Array<T, Alloc>::reference Array<T, Alloc>::operator[](size_type index)
{ // TODO как можно улучшить?? Дублирование кода происходит в < operator[](size_type index) const >
    if (index >= size_ or index < 0)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
Array<T, Alloc>::const_reference Array<T, Alloc>::operator[](size_type index) const
{
    if (index >= size_ or index < 0)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
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
void Array<T, Alloc>::push_back(const value_type &lhs)
{
    if (capacity_ == size_)
        realloc(capacity_ * 2);

    data_[size_ - 1] = lhs;
    ++size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::pop_back() noexcept
{
    if (size_ == 0)
        return; /* По хорошему здесь должно быть выброшено исключение, но метод аннотирован как noexcept
     * throw std::invalid_argument("Error => Attempt to pop empty vector --- [pop_back method]"); */

    data_[size_ - 1].~T(); // вызвать деструктор вложенного объекта
    --size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::push_front(const value_type &rhs)
{
    if (size_ == 0)
        push_back(rhs);
    else
    {
        if (size_ == capacity_)
            realloc(capacity_ * 2);

        for (size_t i = size_; i > 0; i--)
            data_[i] = data_[i - 1];

        data_[0] = rhs;
        ++size_;
    }
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::pop_front() noexcept
{
    if (size_ == 0) /* throw std::invalid_argument("Error => the array is empty --- [pop_front method]"); */
        return; // метод аннотирован noexcept

    for (int i = 0; i < size_-1; i++)
        data_[i] = data_[i + 1];

    --size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::Insert(size_type index, value_type &&value)
{
    if ( (index < 0) or (index > size_) )
        throw std::out_of_range("Index out of range --- [insert method]");

    if (size_ == capacity_)
        realloc(size_ * 2);

    for (int i = size_; i >= index; --i)
        data_[i + 1] = data_[i];

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
    if (index < 0 or index >= size_)
        throw std::out_of_range("Index out of range --- [erase method]");

    for (int i = index; i < size_-1; ++i)
        data_[i] = data_[i + 1];

    --size_;
}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::erase(iterator it)
{

}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::clear() noexcept
{

}
//----------------------------------------------------------------------
template <typename T, typename Alloc>
void Array<T, Alloc>::swap(Array<T> &lhs)
{
    std::swap(data_, lhs.data_);
    std::swap(size_, lhs.size_);
    std::swap(capacity_, lhs.capacity_);
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

    for (size_t i = 0; i < size_; ++i) // уничтожение созданных объектов
        AllocTraits::destroy(alloc_, new_block + i);

    AllocTraits::deallocate(alloc_, data_, capacity_); // возврат памяти

    data_ = new_block;
    capacity_ = new_capacity;
}
//----------------------------------------------------------------------