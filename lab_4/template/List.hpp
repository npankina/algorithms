#include "List.h"

template <typename T>
template <typename Iter>
List<T>::Iterator<Iter>::Iterator(Iter *p) noexcept
: value_(p)
{}
//--------------------------------------------------
template <typename T>
template <typename Iter>
List<T>::Iterator<Iter>::Iterator(const Iter &it) // copy ctor
: value_(it.value_)
{}
//--------------------------------------------------
template <typename T>
template <typename Iter>
bool List<T>::Iterator<Iter>::operator==(const Iterator &it) const noexcept
{
    return value_ == it.value_;
}
//--------------------------------------------------
template <typename T>
template <typename Iter>
bool List<T>::Iterator<Iter>::operator!=(const Iterator &it) const noexcept
{
    return value_ != it.value_;
}
//--------------------------------------------------
template <typename T>
template <typename Iter>
List<T>::Iterator<Iter> &List<T>::Iterator<Iter>::operator++()
{
    return *(++value_);
}
//--------------------------------------------------
template <typename T>
template <typename Iter>
List<T>::Iterator<Iter> &List<T>::Iterator<Iter>::operator--()
{
    return *(--value_);
}
//--------------------------------------------------
template <typename T>
template <typename Iter>
List<T>::Iterator<Iter>::reference List<T>::Iterator<Iter>::operator*()
{
    return *value_;
}
//--------------------------------------------------




//--------------------------------------------------
template <typename T>
List<T>::List() //noexcept(std::is_nothrow_default_constructible<allocator_type>::value)

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