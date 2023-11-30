#include "List.h"

// class Const_Iterator
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator::Const_Iterator(const Node *ptr) noexcept
: current_(ptr)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator::reference List<T>::Const_Iterator::operator*() const noexcept
{
    return *current_;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator& List<T>::Const_Iterator::operator++() noexcept
{
    current_ = current_->next_;
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator& List<T>::Const_Iterator::operator--() noexcept
{
    current_ = current_->prev_;
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator List<T>::Const_Iterator::operator++(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->next_;
    return copy;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator List<T>::Const_Iterator::operator--(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->prev_;
    return copy;
}
//------------------------------------------------------------------------------------------
template <typename T>
bool List<T>::Const_Iterator::operator==(Const_Iterator rhs) const noexcept
{
    return current_ == rhs.current_;
}
//------------------------------------------------------------------------------------------
template <typename T>
bool List<T>::Const_Iterator::operator!=(Const_Iterator rhs) const noexcept
{
    return !(*this == rhs);
}
//------------------------------------------------------------------------------------------
template <typename T>
const List<T>::Node* List<T>::Const_Iterator::Get() const noexcept
{
    return current_;
}
//------------------------------------------------------------------------------------------




// class Iterator
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::Iterator(Node *ptr) noexcept
: Const_Iterator(ptr)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::reference List<T>::Iterator::operator*() const noexcept
{
    auto &&res = std::move(Const_Iterator::operator*());
    return const_cast<reference>(res);
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator &List<T>::Iterator::operator++() noexcept
{
    Const_Iterator::operator++();
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator &List<T>::Iterator::operator--() noexcept
{
    Const_Iterator::operator--();
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator List<T>::Iterator::operator++(int) noexcept
{
    auto res = Const_Iterator::operator++(0);
    return List::Iterator {const_cast<pointer>(res.Get() ) };
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator List<T>::Iterator::operator--(int) noexcept
{
    auto res = Const_Iterator::operator--(0);
    return Iterator {const_cast<pointer>(res.Get() ) };
}
//------------------------------------------------------------------------------------------




// class List
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List()
: size_(0), head_(nullptr), tail_(nullptr)
{}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::~List() // TODO
{
    clear();
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List(const std::initializer_list<value_type> &t)
: List()
{
    for (auto &item : t)
        push_back(item);
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List(const List &other) // copy ctor
: size_(0)
{
    copy(other);
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::List(List &&other) noexcept // move ctor
: size_(other.size_), head_(std::move(other.head_) ), tail_(std::move(other.tail_) )
{}
//------------------------------------------------------------------------------------------
template <typename T> // move assign
List<T> &List<T>::operator=(List &&other) noexcept
{
    if (this != &other)
    {
        size_ = other.size_;
        head_ = std::move(other.head_);
        tail_ = std::move(other.tail_);
    }
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T> // copy assign
List<T> &List<T>::operator=(const List &other)
{
    if (this != &other)
    {
        size_ = other.size_;
        copy(other);
    }
    return *this;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::begin() noexcept
{
    return Const_Iterator(head_);
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::end() noexcept
{
    return Const_Iterator(nullptr);
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::front()
{
    return *head_;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::back()
{
    return *tail_;
}
//------------------------------------------------------------------------------------------
template <typename T>
bool List<T>::empty() const noexcept
{
    return size() == 0;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::size_type List<T>::size() const noexcept
{
    return size_;
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(const_reference lhs)
{
    Node *new_node = new Node(lhs);
    if (head_)
    {
        head_->prev_ = new_node;
        new_node->next_ = head_;
        head_ = new_node;
    }
    else
        head_ = tail_ = new_node;

    ++size_;
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(value_type &&tmp)
{
    Node *new_node = new Node(std::move(tmp) );
    if (head_)
    {
        head_->prev_ = new_node;
        new_node->next_ = head_;
        head_ = new_node;
    }
    else
        head_ = tail_ = new_node;

    ++size_;
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::pop_front()
{
    erase(begin() );
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(const_reference lhs)
{
    Node *new_node = new Node(lhs);

    if (tail_)
    {
        tail_->next_ = new_node;
        new_node->prev_ = tail_;
        tail_ = new_node;
    }
    else
        head_ = tail_ = new_node;

    ++size_;
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(value_type &&tmp)
{
    Node *new_node = new Node(std::move(tmp) );
    if (tail_)
    {
        tail_->next_ = new_node;
        new_node->prev_ = tail_;
        tail_ = new_node;
    }
    else // список пуст
        head_ = tail_ = new_node;

    ++size_;
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::pop_back()
{
    if ( tail_ == head_)
        return;

    tail_->prev_ = nullptr;
    tail_ = tail_->prev_;

    --size_;
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator fnd, const_reference obj)
{
    Node *ptr = const_cast<pointer>(fnd.Get() );
    if (!ptr) // вставка в конец
    {
        push_back(obj);
        return;
    }

    auto new_node = new value_type (obj);
    new_node->next_ = ptr; // т.к. вставляем до итератора
    new_node->prev_ = ptr->prev_;

    if (ptr->prev_) // вставка в голову списка
        ptr->prev_->next_ = new_node;

    ptr->prev_ = new_node;

    ++size_;

    return iterator(ptr);
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::insert(iterator fnd, value_type &&tmp)
{
    auto ptr = const_cast<pointer>(fnd.Get() ); // снятие константности и разыменование указателя

    if (!ptr)
    {
        push_back(std::move(tmp) );
        return;
    }

    auto new_node = new value_type (std::move(tmp) );
    new_node->next_ = ptr;
    new_node->prev_ = ptr->prev_;

    if (ptr->prev_)
        ptr->prev_->next_ = new_node;

    ptr->prev_ = new_node;
    ++size_;

    return iterator(ptr);
}
//------------------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::erase(iterator place)
{
    auto ptr = const_cast<pointer>(place.Get());

    if (ptr->prev_) // не голова списка
        ptr->prev_->next_ = ptr->next_;
    else
        head_ = ptr->next_;

    if (ptr->next_) // не хвост списка
        ptr->next_->prev_ = ptr->prev_;
    else
        tail_ = ptr->prev_;

    delete ptr;
    --size_;

    return iterator(ptr);
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::clear()
{
    while (head_)
        delete std::exchange(head_, head_->next_);
    head_ = tail_ = nullptr;
    size_ = 0;
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::clear(const_iterator it) noexcept
{
    auto ptr = const_cast<pointer>(it.Get() );
    while (ptr) // не хвост списка
        delete std::exchange(ptr, ptr->next_);
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::swap(List &t) noexcept
{
    std::swap(size_, t.size_);
    std::swap(head_, t.head_);
    std::swap(tail_, t.tail_);
}
//------------------------------------------------------------------------------------------
template <typename T>
void List<T>::copy(const List &obj)
{
    Node *new_obj = obj.head_;
    iterator it = begin();

    // если A < B копировать до A.size(); создать новые элементы в А после позиции A.size()
    if (size() < obj.size() )
    {
        while (it != end())
        {
            *it = new_obj->data_;
            new_obj = new_obj->next_;
            ++it;
        }
        while (new_obj != nullptr)
        {
            push_back(new_obj->data_);
            new_obj = new_obj->next_;
        }
    }
    else
    {
        while (new_obj != nullptr)
        {
            *it = new_obj->data_;
            new_obj = new_obj->next_;
            ++it;
        }

        if (size() > obj.size() )
        {
            tail_ = &(*it);
            clear(it); // удаляем элементы с новой позиции хвоста А
        }
    }
}
//------------------------------------------------------------------------------------------