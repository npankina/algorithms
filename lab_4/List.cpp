#include "List.h"

// class Node
//----------------------------------------------------------------------
Node::Node()
: prev_(nullptr), next_(nullptr)
{}
//----------------------------------------------------------------------
Node::Node(const int &value, Node *prev, Node *next) // copy ctor
: data_(value), prev_(prev), next_(next)
{}
//----------------------------------------------------------------------
Node::Node(Node *prev, const int &&value, Node *next) // move ctor
: prev_(prev), next_(next)
{
    data_ = std::move(value);
    if (prev == nullptr or next == nullptr) // выбросить исключение nullptr
        throw 22; // объект не будет создан
}
//----------------------------------------------------------------------
Node::Node(Node *prev, Node *next)
: prev_(prev), next_(next)
{}
//----------------------------------------------------------------------



// class iterator
//----------------------------------------------------------------------
List::iterator::iterator(value_type *t) noexcept
: ptr_(t)
{}
//----------------------------------------------------------------------
List::iterator::iterator() noexcept
: ptr_(nullptr)
{}
//----------------------------------------------------------------------
bool List::iterator::operator==(const iterator &it) const noexcept
{
    return ptr_ == it.ptr_;
}
//----------------------------------------------------------------------
bool List::iterator::operator!=(const iterator &it) const noexcept
{
    return ptr_ != it.ptr_;
}
//----------------------------------------------------------------------
List::iterator &List::iterator::operator++() noexcept
{
    ++ptr_;
    return *this;
}
//----------------------------------------------------------------------
List::iterator &List::iterator::operator++(int) noexcept
{
    iterator copy{*this};
    ++ptr_;
    return copy;
}
//----------------------------------------------------------------------
List::iterator &List::iterator::operator--() noexcept
{
    --ptr_;
    return *this;
}
//----------------------------------------------------------------------
List::iterator &List::iterator::operator--(int) noexcept
{
    iterator copy{*this};
    --ptr_;
    return copy;
}
//----------------------------------------------------------------------
List::reference List::iterator::operator*() const noexcept
{
    return *ptr_;
}
//----------------------------------------------------------------------



// class List
//----------------------------------------------------------------------
List::List(size_type sz)
: size_(sz), head_(new Node()), tail_(new Node())
{
    head_->next_ = tail_;
    tail_->prev_ = head_;
}
//----------------------------------------------------------------------
List::~List()
{ // пройти по всей цепочке и удалить каждую Node

}
//----------------------------------------------------------------------
List::List(const std::initializer_list<value_type> &t)
: List()
{
    for (auto item : t)
        push_front(item);
}
//----------------------------------------------------------------------
List::List(const List& other) noexcept // copy ctor
: size_(other.size_), head_(other.head_), tail_(other.tail_)
{}
//----------------------------------------------------------------------
List::List(List&& other) noexcept // move ctor
: size_(other.size_), head_(std::move(other.head_)), tail_(std::move(other.tail_))
{}
//----------------------------------------------------------------------
List &List::operator=(List&& other) noexcept // move assign
{ // -- операция перемещения --
    size_ = other.size_;
    head_ = std::move(other.head_);
    tail_ = std::move(other.tail_);
}
//----------------------------------------------------------------------
List &List::operator=(const List& other) // copy assign
{
    size_ = other.size_;
    head_ = other.head_;
    tail_ = other.tail_;
}
//----------------------------------------------------------------------
List::iterator List::begin() noexcept
{
    return iterator(head_->next_);
}
//----------------------------------------------------------------------
List::iterator List::end() noexcept
{
    return iterator(tail_);
}
//----------------------------------------------------------------------
List::reference List::front()
{
    return *head_;
}
//----------------------------------------------------------------------
List::reference List::back()
{
    return *tail_;
}
//----------------------------------------------------------------------
bool List::empty() const noexcept
{
    return size_ == 0;
}
//----------------------------------------------------------------------
List::size_type List::size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------
void List::push_front(const_reference rhs)
{ // добавить в начало; Time Complexity: O(1)
    Node *new_node = new Node(rhs);

    new_node->prev_ = head_;
    new_node->next_ = head_->next_;
    head_->next_ = new_node;
    (new_node->next_)->prev_ = new_node->next_;

    ++size_;
}
//----------------------------------------------------------------------
void List::push_front(value_type &&tmp)
{ // добавить в начало - временный объект --
    Node *new_node = new Node(std::move(tmp));

    new_node->prev_ = head_;
    new_node->next_ = head_->next_;
    head_->next_ = new_node;
    new_node->next_->prev_ = new_node->next_;

    ++size_;
}
//----------------------------------------------------------------------
void List::pop_front()
{ // удалить первый

}
//----------------------------------------------------------------------
void List::push_back(const_reference)
{ // добавить в конец

}
//----------------------------------------------------------------------
void List::push_back(value_type &&)
{ // добавить в начало - временный объект --

}
//----------------------------------------------------------------------
void List::pop_back()
{ // удалить последний

}
//----------------------------------------------------------------------
//List::iterator List::insert(iterator fnd, const_reference obj)
//{ // вставить в позицию итератора
//
//    for (auto it = begin(); it != end(); it++)
//    {
//        if (it == fnd) // итератор
//        {
//            reference new_obj = *obj;
//            reference current_nd = *it;
//            reference next_nd = *(it++);
//
//            current_nd.next_ = new_obj;
//            next_nd.prev_ = new_obj;
//            new_obj.prev_ = current_nd;
//            new_obj.next_ = next_nd;
//            return fnd;
//        }
//    }
//    return nullptr;
//}
//----------------------------------------------------------------------
List::iterator List::insert(iterator, value_type&&)
{  // вставить временный объект --

}
//----------------------------------------------------------------------
List::iterator List::erase(iterator)
{ // удалить указанный (в позиции)

}
//----------------------------------------------------------------------
//void List::clear()
//{ // удалить все
//    size_ = 0;
//
//    for (auto it = begin(); it != end(); it++)
//    {
//        delete *it;
//    }
//
//    head_ = nullptr;
//    tail_ = nullptr;
//}
//----------------------------------------------------------------------
//void List::swap(List &t) noexcept
//{
//    this = std::move(t);
//}
//----------------------------------------------------------------------

#if template
// class Node
//----------------------------------------------------------------------
Node<T>::Node()
: prev_(nullptr), next_(nullptr)
{}
//----------------------------------------------------------------------
Node<T>::Node(Node *prev, const T &value, Node *next) // copy ctor
: prev_(prev), next_(next)
{
    value = std::copy(value);
}
//----------------------------------------------------------------------
Node<T>::Node(Node *prev, const T &&value, Node *next) // move ctor
: prev_(prev), next_(next)
{
    data_ = std::move(value);
    if (prev == nullptr or next == nullptr) // выбросить исключение nullptr
        throw 22; // объект не будет создан
}
//----------------------------------------------------------------------
Node<T>::Node(Node *prev, Node *next)
: prev_(prev), next_(next)
{}
//----------------------------------------------------------------------



// class iterator
//----------------------------------------------------------------------
List<T>::iterator::iterator(Node<T> *t) noexcept
: ptr_(t)
{}
//----------------------------------------------------------------------
List<T>::iterator::iterator() noexcept
: ptr_(nullptr)
{}
//----------------------------------------------------------------------
bool List<T>::iterator::operator==(const iterator &it) const noexcept
{
    return ptr_ == *it; // вернет Node
}
//----------------------------------------------------------------------
bool List<T>::iterator::operator!=(const iterator &it) const noexcept
{
    return ptr_ != *it;
}
//----------------------------------------------------------------------
List<T>::iterator &List<T>::iterator::operator++()
{
    return iterator(ptr_++);
}
//----------------------------------------------------------------------
List<T>::iterator &List<T>::iterator::operator--()
{
    return iterator(ptr_--);
}
//----------------------------------------------------------------------
List<T>::reference List<T>::iterator::operator*()
{
    return *ptr_;
}
//----------------------------------------------------------------------

// class iterator
//----------------------------------------------------------------------
List<T>::iterator::iterator(Node *t) noexcept
: ptr_(t)
{}
//----------------------------------------------------------------------
List<T>::iterator::iterator() noexcept
: ptr_(nullptr)
{}
//----------------------------------------------------------------------
bool List<T>::iterator::operator==(const iterator &it) const noexcept
{
    return ptr_ == *it; // вернет Node
}
//----------------------------------------------------------------------
bool List<T>::iterator::operator!=(const iterator &it) const noexcept
{
    return ptr_ != *it;
}
//----------------------------------------------------------------------
List<T>::iterator &List<T>::iterator::operator++()
{
    return iterator(ptr_++);
}
//----------------------------------------------------------------------
List<T>::iterator &List<T>::iterator::operator--()
{
    return iterator(ptr_--);
}
//----------------------------------------------------------------------
List<T>::reference List<T>::iterator::operator*()
{
    return *ptr_;
}
//----------------------------------------------------------------------



// class List
//----------------------------------------------------------------------
List<T>::List(size_type sz)
: size_(sz), head_(new Node()), tail_(new Node())
{
    head_->next_ = tail_;
    tail_->prev_ = head_;
}
//----------------------------------------------------------------------
List<T>::~List()
{ // пройти по всей цепочке и удалить каждую Node

}
//----------------------------------------------------------------------
List<T>::List(const std::initializer_list<value_type> &t)
: List(t.size() )
{
    for (auto item : t)
        push_front(item);
}
//----------------------------------------------------------------------
List<T>::List(const List& other) // copy ctor
{}
//----------------------------------------------------------------------
List<T>::List(List&& other) noexcept // move ctor
{ // -- конструктор переноса --

}
//----------------------------------------------------------------------
List<T> &List<T>::operator=(List&& other) noexcept // move assign
{ // -- операция перемещения --

}
//----------------------------------------------------------------------
List<T> &List<T>::operator=(const List& other) // copy assign
{}
//----------------------------------------------------------------------
List<T>::iterator List<T>::begin() noexcept
{
    return iterator(head_);
}
//----------------------------------------------------------------------
List<T>::iterator List<T>::end() noexcept
{
    return iterator(tail_);
}
//----------------------------------------------------------------------
List<T>::reference List<T>::front()
{
    return head_;
}
//----------------------------------------------------------------------
List<T>::reference List<T>::back()
{
    return tail_;
}
//----------------------------------------------------------------------
bool List<T>::empty() const noexcept
{
    return size_ == 0;
}
//----------------------------------------------------------------------
List<T>::size_type List<T>::size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------
void List<T>::push_front(const_reference rhs)
{ // добавить в начало; Time Complexity: O(1)
    T *new_node = new Node(rhs);

    new_node->prev_ = &head_;
    new_node->next = head_->next_;
    head_->next_ = &new_node;
    (new_node->next_)->prev_ = new_node->next_;

    ++size_;
}
//----------------------------------------------------------------------
void List<T>::push_front(value_type &&tmp)
{ // добавить в начало - временный объект --
    T *new_node = std::move(tmp);

    new_node->prev_ = &head_;
    new_node->next = head_->next_;
    head_->next_ = &new_node;
    new_node->next_->prev_ = new_node->next_;

    ++size_;
}
//----------------------------------------------------------------------
void List<T>::pop_front()
{ // удалить первый

}
//----------------------------------------------------------------------
void List<T>::push_back(const_reference)
{ // добавить в конец

}
//----------------------------------------------------------------------
void List<T>::push_back(value_type &&)
{ // добавить в начало - временный объект --

}
//----------------------------------------------------------------------
void List<T>::pop_back()
{ // удалить последний

}
//----------------------------------------------------------------------
List<T>::iterator List<T>::insert(iterator fnd, const_reference obj)
{ // вставить в позицию итератора

    for (auto it = begin(); it != end(); it++)
    {
        if (it == fnd) // итератор
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
List<T>::iterator List<T>::insert(iterator, value_type&&)
{  // вставить временный объект --

}
//----------------------------------------------------------------------
List<T>::iterator List<T>::erase(iterator)
{ // удалить указанный (в позиции)

}
//----------------------------------------------------------------------
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
void List<T>::swap(List &t) noexcept
{
    this = std::move(t);
}
//----------------------------------------------------------------------
#endif