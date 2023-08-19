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
        throw std::exception();
}
//----------------------------------------------------------------------
template <typename T>
Node<T>::Node(Node *prev, Node *next)
: prev_(prev), next_(next)
{}
//----------------------------------------------------------------------


#if need
// class iterator
//----------------------------------------------------------------------
List::iterator::iterator(Node *t) noexcept
{}
//----------------------------------------------------------------------
List::iterator::iterator() noexcept
{}
//----------------------------------------------------------------------
bool List::iterator::operator==(const iterator &it) const noexcept
{}
//----------------------------------------------------------------------
bool List::iterator::operator!=(const iterator &it) const noexcept
{}
//----------------------------------------------------------------------
List::iterator &List::iterator::operator++()
{}
//----------------------------------------------------------------------
List::iterator &List::iterator::operator--()
{}
//----------------------------------------------------------------------
List::reference List::iterator::operator*()
{}
//----------------------------------------------------------------------
#endif



// class List
//----------------------------------------------------------------------
template <typename T>
List<T>::List()
: size_(0), head_(nullptr), tail_(nullptr)
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::~List()
{}
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
List<T>::List(const List& other)
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::List(List&& other) noexcept
{ // -- конструктор переноса --

}
//----------------------------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(List&& other) noexcept
{ // -- операция перемещения --

}
//----------------------------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(const List& other)
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::begin() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::end() noexcept
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::front()
{}
//----------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::back()
{}
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
List<T>::iterator List<T>::insert(iterator, const_reference)
{ // вставить в позицию итератора

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
    head_ = nullptr;
    tail_ = nullptr;
}
//----------------------------------------------------------------------
template <typename T>
void List<T>::swap(List &t) noexcept
{

}
//----------------------------------------------------------------------