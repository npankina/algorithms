#include "Array.h"

// class Array
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array()
: size_(0), allocated_(10)
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(const size_type &n, value_type t)
: size_(n), allocated_(n + 10), data_(new value_type[allocated_])
{
    for (auto i = 0; i < n; ++i) // TODO ?? уместнее использовать std::fill
        data_[i] = t;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(const std::initializer_list<value_type> &t)
: size_(t.size() ), allocated_(size_ * 2), data_(new value_type[allocated_])
// TODO ?? потенциальная ошибка при выделении памяти. Как поведет себя программа, если память выделиться не сможет?
{
    for (auto i : t)
        push_back(i);
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(const Array &lhs) // copy ctor
: size_(lhs.size_), allocated_(lhs.allocated_), data_(new value_type[allocated_])
{
    std::copy(lhs.data_, lhs.data_ + size_, data_);
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(Array &&rhs) noexcept // move ctor
: size_(rhs.size_), allocated_(rhs.allocated_), data_(std::move(rhs.data_) )
{ // обнуление старого объекта
    rhs.size_ = 0;
    rhs.allocated_ = 0;
    rhs.data_ = nullptr;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>& Array<T>::operator=(const Array &lhs) // copy assign
{
    if (this != &lhs)
    {
        size_ = lhs.size_;
        allocated_ = lhs.allocated_;
        data_.~T();
        data_ = new value_type[allocated_];
        std::copy(lhs.data_, lhs.data_ + size_, data_);
    }

    return *this;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>& Array<T>::operator=(Array &&rhs) noexcept // move assign
{
    if (this != &rhs)
    {
        std::swap(size_, rhs.size_);
        std::swap(allocated_, rhs.allocated_);
        data_.~T();
        data_ = std::move(rhs.data_);
    }

    return *this;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::~Array() noexcept
{
    delete [] data_;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::size_type Array<T>::size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------
template <typename T>
bool Array<T>::empty() const noexcept
{
    return size_ == 0;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::size_type Array<T>::capacity() const noexcept
{
    return allocated_;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::iterator begin() noexcept
{
    return data_[0];
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::iterator Array<T>::end() noexcept
{
    return data_ + size_;
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::reference Array<T>::operator[](size_type index)
{ // TODO как можно улучшить?? Дублирование кода происходит
    if (index >= size_ or index < 0)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::const_reference Array<T>::operator[](size_type index) const
{
    if (index >= size_ or index < 0)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::reference Array<T>::front() noexcept
{
    return data_[0];
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::const_reference Array<T>::front() const noexcept
{
    return data_[0];
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::reference Array<T>::back() noexcept
{
    return data_[size_ - 1];
}
//----------------------------------------------------------------------
template <typename T>
Array<T>::const_reference Array<T>::back() const noexcept
{
    return data_[size_ - 1];
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::push_back(const value_type &lhs)
{
    if (allocated_ == size_)
        realloc(allocated_ * 2);

    data_[size_ - 1] = lhs;
    ++size_;
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::realloc(size_type new_capacity)
{
    // 1. Allocate a new block of memory
    // 2. copy / move old elements into new block
    // 3. delete old block

    // TODO ?? защита от вылета операции new

    auto *new_block = new value_type [new_capacity];

    if (new_capacity > size_)
        size_ = new_capacity;

    for (int i = 0; i < size_; i++)
        new_block[i] = data_[i];

    delete [] data_;
    data_ = std::move(new_block);
    allocated_ = new_capacity;
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::pop_back() noexcept
{
    if (size_ == 0)
        return; // Nothing to pop

    (data_ + size_)->~T(); // вызвать деструктор вложенного объекта
    --size_;
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::push_front(const value_type &lhs)
{
    if (size_ == 0)
        push_back(lhs);
    else
    {
        if (size_ == allocated_)
            realloc(allocated_ * 2);

        for (size_t i = size_; i > 0; i--)
            data_[i] = data_[i - 1];

        data_[0] = lhs;
        ++size_;
    }
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::pop_front() noexcept
{
    if (size_ == 0)
    {
        std::cout << "Error => the array is empty --- [pop_front method]" << std::endl;
        return;
    }

    for (int i = 0; i < size_-1; i++)
        data_[i] = data_[i + 1];

    --size_;
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::Insert(size_type index, value_type &&value)
{
    if ( (index < 0) or (index > size_) )
    {
        std::cout << "Error => Index out of range --- [insert method]" << std::endl;
        return;
    }

    if (size_ == allocated_)
        realloc(size_ * 2);

    for (int i = size_; i >= index; --i)
        data_[i + 1] = data_[i];

    data_[index] = value;
    ++size_;
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::insert(iterator it, value_type &&value)
{
    // TODO сделать

}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::erase(size_type index)
{
    if (index < 0 || index >= size_)
        throw std::out_of_range("index out of range");

    for (int i = index; i < size_-1; ++i)
        data_[i] = data_[i + 1];

    --size_;
}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::erase(iterator it)
{

}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::clear() noexcept
{

}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::swap(Array &lhs)
{
    std::swap(data_, lhs.data_);
    std::swap(size_, lhs.size_);
    std::swap(allocated_, lhs.allocated_);
}
//----------------------------------------------------------------------