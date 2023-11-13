#include "List.h"

// class Iterator
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::Iterator(const Node *ptr) noexcept
: current_(ptr)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::Iterator()
: current_(nullptr)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::reference List<T>::Iterator::operator*() const noexcept
{
    return *current_;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator &List<T>::Iterator::operator++() noexcept
{
    current_ = current_->next_;
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator &List<T>::Iterator::operator--() noexcept
{
    current_ = current_->prev_;
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator List<T>::Iterator::operator++(int) noexcept
{
    List::Iterator copy = *this;
    current_ = current_->next_;
    return copy;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator List<T>::Iterator::operator--(int) noexcept
{
    List::Iterator copy = *this;
    current_ = current_->prev_;
    return copy;
}
//------------------------------------------------------------------------------------------
template <typename T>
bool List<T>::Iterator::operator==(Iterator rhs) const noexcept
{
    return current_ == rhs.current_;
}
//------------------------------------------------------------------------------------------
template <typename T>
bool List<T>::Iterator::operator!=(Iterator rhs) const noexcept
{
    return !(*this == rhs);
}
//------------------------------------------------------------------------------------------




// class List
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List()
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::~List()
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List(const std::initializer_list<value_type> &t)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List(const List& other) // copy ctor
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List(List&& other) noexcept // move ctor
{}
//------------------------------------------------------------------------------------------
template <typename T> // move assign
List<T> &List<T>::operator=(List&& other) noexcept
{}
//------------------------------------------------------------------------------------------
template <typename T> // copy assign
List<T> &List<T>::operator=(const List& other)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::begin() noexcept
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::end() noexcept
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::reference front()
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::reference back()
{}
//------------------------------------------------------------------------------------------
template <typename T>
bool List<T>::empty() const noexcept
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::size_type List<T>::size() const noexcept
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(const_reference)
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(value_type &&)
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::pop_front()
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(const_reference)
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(value_type &&)
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::pop_back()
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator, const_reference)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator, value_type&&)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::erase(iterator)
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::clear()
{}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::swap(List &t) noexcept
{}
//------------------------------------------------------------------------------------------