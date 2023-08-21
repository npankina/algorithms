#include "List.h"

// class Node
//----------------------------------------------------------------------
template <typename T>
Node<T>::Node()
: prev_(nullptr), next_(nullptr)
{}
//----------------------------------------------------------------------
template <typename T>
Node<T>::Node(Node *prev, const T &value, Node *next) // copy ctor
: prev_(prev), next_(next)
{
    value = std::copy(value);
}
//----------------------------------------------------------------------
template <typename T>
Node<T>::Node(Node *prev, const T &&value, Node *next) // move ctor
: prev_(prev), next_(next)
{
    data_ = std::move(value);
    if (prev == nullptr or next == nullptr) // выбросить исключение nullptr
        throw 22; // объект не будет создан
}
//----------------------------------------------------------------------
template <typename T>
Node<T>::Node(Node *prev, Node *next)
: prev_(prev), next_(next)
{}
//----------------------------------------------------------------------



// class iterator
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator::iterator(Node<T> *t) noexcept
: ptr_(t)
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator::iterator() noexcept
: ptr_(nullptr)
{}
//----------------------------------------------------------------------
template <typename T>
bool List<T>::iterator::operator==(const iterator &it) const noexcept
{
    return ptr_ == *it; // вернет Node
}
//----------------------------------------------------------------------
template <typename T>
bool List<T>::iterator::operator!=(const iterator &it) const noexcept
{
    return ptr_ != *it;
}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator &List<T>::iterator::operator++()
{
    return iterator(ptr_++);
}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator &List<T>::iterator::operator--()
{
    return iterator(ptr_--);
}
//----------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::iterator::operator*()
{
    return *ptr_;
}
//----------------------------------------------------------------------




// class List
//----------------------------------------------------------------------
template <typename T>
List<T>::List()
: size_(0), head_(nullptr), tail_(nullptr)
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::~List()
{ // пройти по всей цепочке и удалить каждую Node

}
//----------------------------------------------------------------------
template <typename T>
List<T>::List(const std::initializer_list<value_type> &t)
: size_(t.size()), head_(nullptr), tail_(nullptr)
{
    for (auto item : t)
        push_front(item);
}
//----------------------------------------------------------------------
template <typename T>
List<T>::List(const List& other) // copy ctor
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::List(List&& other) noexcept // move ctor
{ // -- конструктор переноса --

}
//----------------------------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(List&& other) noexcept // move assign
{ // -- операция перемещения --

}
//----------------------------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(const List& other) // copy assign
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::begin() noexcept
{
    return iterator(head_);
}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::end() noexcept
{
    return iterator(tail_);
}
//----------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::front()
{
    return head_;
}
//----------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::back()
{
    return tail_;
}
//----------------------------------------------------------------------
template <typename T>
bool List<T>::empty() const noexcept
{
    return size_ == 0;
}
//----------------------------------------------------------------------
template <typename T>
List<T>::size_type List<T>::size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------
template <typename T>
void List<T>::push_front(const_reference rhs)
{ // добавить в начало; Time Complexity: O(1)
    T *new_node = new Node(rhs);

    if (head_ != nullptr)
    {
        head_->next = new_node;
        new_node->prev_ = head_;
    }

    head_ = new_node;
    new_node->next_ = nullptr;
    new_node->data_ = rhs.data_;

    ++size_;
}
//----------------------------------------------------------------------
template <typename T>
void List<T>::push_front(value_type &&tmp)
{ // добавить в начало - временный объект --
    T *new_node = std::move(tmp);

    if (head_ != nullptr)
    {
        head_->next = new_node;
        new_node->prev_ = head_;
    }

    head_ = new_node;
    new_node->next_ = nullptr;
    new_node->data_ = tmp.data_;

    ++size_;
}
//----------------------------------------------------------------------
template <typename T>
void List<T>::pop_front()
{ // удалить первый

}
//----------------------------------------------------------------------
template <typename T>
void List<T>::push_back(const_reference)
{ // добавить в конец

}
//----------------------------------------------------------------------
template <typename T>
void List<T>::push_back(value_type &&)
{ // добавить в начало - временный объект --

}
//----------------------------------------------------------------------
template <typename T>
void List<T>::pop_back()
{ // удалить последний

}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator fnd, const_reference obj)
{ // вставить в позицию итератора

    for (auto it = begin(); it != end(); it++)
    {
        // итератор
        if (it == fnd)
        {
            reference new_obj = *obj;
            reference current_nd = *it;
            reference next_nd = *(it++);

            current_nd.next_ = new_obj;
            next_nd.prev_ = new_obj;
            new_obj.prev_ = current_nd;
            new_obj.next_ = next_nd;
            return fnd;
        }
    }
    return nullptr;
}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator, value_type&&)
{  // вставить временный объект --

}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::erase(iterator)
{ // удалить указанный (в позиции)

}
//----------------------------------------------------------------------
template <typename T>
void List<T>::clear()
{ // удалить все
    size_ = 0;

    for (auto it = begin(); it != end(); it++)
    {
        delete *it;
    }

    head_ = nullptr;
    tail_ = nullptr;
}
//----------------------------------------------------------------------
template <typename T>
void List<T>::swap(List &t) noexcept
{
    this = std::move(t);
}
//----------------------------------------------------------------------