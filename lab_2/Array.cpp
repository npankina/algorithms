#include "Array.h"

// class Array
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array()
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(const size_type &n, value_type t)
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(const std::initializer_list<value_type> &t)
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(const Array &lhs)
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::Array(Array &&rhs) noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>& Array<T>::operator=(const Array &lhs)
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>& Array<T>::operator=(Array &&rhs) noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::~Array() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::size_type Array<T>::size() const noexcept
{}
//----------------------------------------------------------------------
template <typename T>
bool Array<T>::empty() const noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::size_type Array<T>::capacity() const noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::iterator begin() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::iterator Array<T>::end() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::reference Array<T>::operator[](size_type)
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::const_reference Array<T>::operator[](size_type index) const
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::reference Array<T>::front() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::const_reference Array<T>::front() const noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::reference Array<T>::back() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
Array<T>::const_reference Array<T>::back() const noexcept
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::push_back(const value_type &lhs)
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::pop_back() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::push_front(const value_type &lhs)
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::pop_front() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::Insert(size_type idx)
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::insert(iterator it)
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::erase(size_type idx)
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::erase(iterator it)
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::clear() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
void Array<T>::swap(Array &lhs)
{}
//----------------------------------------------------------------------