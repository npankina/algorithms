#include "List.h"

template <typename T>
List<T>::iterator::iterator() noexcept
//: ptr_()
{

}
//--------------------------------------------------
template <typename T>
bool List<T>::iterator::operator==(const iterator &it) const noexcept
{
    return ptr_ == it.ptr_;
}
//--------------------------------------------------
template <typename T>
bool List<T>::iterator::operator!=(const iterator &it) const noexcept
{
    return ptr_ != it.ptr_;
}
//--------------------------------------------------
template <typename T>
List<T>::iterator &List<T>::iterator::operator++()
{
    return *(++ptr_);
}
//--------------------------------------------------
template <typename T>
List<T>::iterator &List<T>::iterator::operator--()
{
    return *(--ptr_);
}
//--------------------------------------------------
template <typename T>
List<T>::reference List<T>::iterator::operator*()
{
    return *ptr_;
}
//--------------------------------------------------




//--------------------------------------------------
template <typename T>
List<T>::List()
{

}
//--------------------------------------------------
template <typename T>
List<T>::~List()
{

}
//--------------------------------------------------
template <typename T>
List<T>::List(const std::initializer_list <value_type> &t)
{

}
//--------------------------------------------------
template <typename T>
List<T>::List(const List &other) // copy ctor
{

}
//--------------------------------------------------
template <typename T>
List<T>::List(List &&other) noexcept // move ctor
{

}
//--------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(List &&other) noexcept // move assign
{

}
//--------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(const List &other) // copy assign
{

}
//--------------------------------------------------
template <typename T>
List<T>::iterator List<T>::begin() const noexcept
{
    return data_;
}
//--------------------------------------------------
template <typename T>
List<T>::iterator List<T>::end() const noexcept
{
    return data_ + size_;
}
//--------------------------------------------------
template <typename T>
List<T>::reference List<T>::front()
{

}
//--------------------------------------------------
template <typename T>
List<T>::reference List<T>::back()
{

}
//--------------------------------------------------
template <typename T>
bool List<T>::empty() const noexcept
{

}
//--------------------------------------------------
template <typename T>
List<T>::size_type List<T>::size() const noexcept
{

}
//--------------------------------------------------
template <typename T>
void List<T>::push_front(const_reference)
{

}
//--------------------------------------------------
template <typename T>
void List<T>::push_front(value_type &&)
{

}
//--------------------------------------------------
template <typename T>
void List<T>::pop_front()
{

}
//--------------------------------------------------
template <typename T>
void List<T>::push_back(const_reference)
{

}
//--------------------------------------------------
template <typename T>
void List<T>::push_back(value_type &&)
{

}
//--------------------------------------------------
template <typename T>
void List<T>::pop_back()
{

}
//--------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator, const_reference)  // вставить в позицию итератора
{

}
//--------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator, value_type &&)     // вставить временный объект
{

}
//--------------------------------------------------
template <typename T>
List<T>::iterator List<T>::erase(iterator pos)   // удалить указанный (в позиции)
{

}
//--------------------------------------------------
template <typename T>
void List<T>::clear()  // удалить все
{

}
//--------------------------------------------------
template <typename T>
void List<T>::swap(List &t) noexcept
{

}