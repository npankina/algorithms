#include "List.h"


//--------------------------------------------------------------------------------
template <typename T>
std::ostream &operator<<(std::ostream &os, List<T> &list)
{
    int i = 0;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        os << "#" << ++i << '\n';
        os << "Catalog ID: " << (*it).data_.Get_cypher() << "\n";
        os << "Year of publishing: " << (*it).data_.Get_year_of_pub() << "\n";
        os << "Publisher: " << (*it).data_.Get_publisher() << "\n";
        os << "Price: " << (*it).data_.Get_price_() << "\n\n";
    }

    return os;
}
//--------------------------------------------------------------------------------




// class Node
//--------------------------------------------------------------------------------
List::Node::Node(Record item) noexcept
        : prev_(nullptr), next_(nullptr), data_{ std::move(item) }
{}
//--------------------------------------------------------------------------------
List::Node::Node(const Node &lhs)
        : prev_(lhs.prev_), next_(lhs.next_),
          data_{ lhs.data_.Get_cypher(),lhs.data_.Get_year_of_pub(),
                 lhs.data_.Get_publisher(), lhs.data_.Get_price_() }
{}
//--------------------------------------------------------------------------------
List::Node::Node(Node &&rhs) // move ctor
        : prev_(std::move(rhs.prev_) ), next_(std::move(rhs.next_) ),
          data_(std::move(std::make_tuple(
                  rhs.data_.Get_cypher(), rhs.data_.Get_year_of_pub(),
                  rhs.data_.Get_publisher(),rhs.data_.Get_price_())) )
{}
//--------------------------------------------------------------------------------
List::Node &List::Node::operator=(const Node &lhs)
{
    if (this != &lhs)
    {
        prev_ = lhs.prev_;
        next_ = lhs.next_;
        data_ = { lhs.data_.Get_cypher(), lhs.data_.Get_year_of_pub(),
                  lhs.data_.Get_publisher(), lhs.data_.Get_price_() };
    }
    return *this;
}
//--------------------------------------------------------------------------------
List::Node &List::Node::operator=(Node &&rhs) noexcept // move assign
{
    if (this != &rhs)
    {
        std::swap(prev_, rhs.prev_);
        std::swap(next_, rhs.next_);
        std::swap(data_, rhs.data_);
    }
    return *this;
}
//--------------------------------------------------------------------------------
bool List::Node::operator==(const_reference item) const noexcept
{
    return data_ == item.data_;
}
//--------------------------------------------------------------------------------




// class Const_Iterator
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator::Const_Iterator(const value_type *ptr) noexcept
: current_(ptr)
{}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator::reference List<T>::Const_Iterator::operator*() const noexcept
{
    return *current_;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator &List<T>::Const_Iterator::operator++() noexcept
{
    current_ = current_->next_;
    return *this;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator &List<T>::Const_Iterator::operator--() noexcept
{
    current_ = current_->prev_;
    return *this;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator List<T>::Const_Iterator::operator++(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->next_;
    return copy;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator List<T>::Const_Iterator::operator--(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->prev_;
    return copy;
}
//--------------------------------------------------------------------------------
template <typename T>
bool List<T>::Const_Iterator::operator==(Const_Iterator rhs) const noexcept
{
    return current_ == rhs.current_;
}
//--------------------------------------------------------------------------------
template <typename T>
bool List<T>::Const_Iterator::operator!=(Const_Iterator rhs) const noexcept
{
    return !(*this == rhs);
}
//--------------------------------------------------------------------------------
template <typename T>
const List<T>::Node *List<T>::Const_Iterator::Get() const noexcept
{
    return current_;
}
//--------------------------------------------------------------------------------




// class Iterator
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::Iterator(value_type *ptr) noexcept
: Const_Iterator(ptr)
{}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::Iterator::operator*() const noexcept
{
    auto &&res = std::move(Const_Iterator::operator*());
    return const_cast<reference>(res);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator &List<T>::Iterator::operator++() noexcept
{
    Const_Iterator::operator++();
    return *this;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator &List<T>::Iterator::operator--() noexcept
{
    Const_Iterator::operator--();
    return *this;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator List<T>::Iterator::operator++(int) noexcept
{
    auto res = Const_Iterator::operator++(0);
    return List::Iterator {const_cast<pointer>(res.Get() ) };
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Iterator List<T>::Iterator::operator--(int) noexcept
{
    auto res = Const_Iterator::operator--(0);
    return Iterator {const_cast<pointer>(res.Get() ) };
}
//--------------------------------------------------------------------------------




// class List
//--------------------------------------------------------------------------------
template <typename T>
List<T>::List()
: size_(0), head_(nullptr), tail_(nullptr)
{}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::List(const std::initializer_list<value_type> &items)
: List()
{
    for (auto &item : t)
        push_back(item);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::List(const List &other) noexcept          // copy ctor
: size_(other.size() ), head_(nullptr), tail_(nullptr)
{   // Задача - произвести правильное копирование (deep copy)

    // TODO
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::List(List &&other) noexcept              // move ctor
: size_(other.size() ), head_(nullptr), tail_(nullptr)
{ // std::swap зануляет temp obj
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(List &&other) noexcept // move assign
{
    if (this != other and size_ > 0)
    {
        size_ = std::move(other.size_);
        head_ = std::move(other.head_);
        tail_ = std::move(other.tail_);
    }

    return *this;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T> &List<T>::operator=(const List &other)     // copy assign
{
    if (this != other and size_ > 0)
    {
        size_ = other.size();
        copy(other);
    }

    return *this;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::~List()
{
    clear();
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::const_iterator List<T>::begin() const noexcept
{
    return const_iterator(head_);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::const_iterator List<T>::end() const noexcept
{
    return const_iterator(nullptr);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::begin() noexcept
{
    return iterator(head_);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::end() noexcept
{
    return iterator(nullptr);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::front()
{
    return *head_;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::reference List<T>::back()
{
    return *tail_;
}
//--------------------------------------------------------------------------------
template <typename T>
bool List<T>::is_empty() const noexcept
{
    return size_ == 0;
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::size_type List<T>::size() const noexcept
{
    return size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(const_reference rhs)
{ // добавить в начало; Time Complexity: O(1)

    Node *new_item = new Node(rhs);
    if (head_) // если список > 0
    {
        head_->prev = new_item;
        new_item->next = head_;
        head_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(value_type &&tmp)
{ // добавить в начало - временный объект --

    Node *new_item = std::move(tmp);
    if (head_) // если список > 0
    {
        head_->prev = new_item;
        new_item->next = head_;
        head_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::pop_front() noexcept
{ // удалить первый
    if (size_ == 0)
        return;

    erase(begin() );
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(const_reference obj)
{ // добавить в конец
    auto new_item = new Node(obj);

    if (tail_)
    {
        tail_->next = new_item;
        new_item->prev = tail_;
        tail_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(value_type &&tmp)
{ // добавить в начало - временный объект --
    auto new_item = std::move(tmp);

    if (tail_)
    {
        tail_->next = new_item;
        new_item->prev = tail_;
        tail_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::pop_back() noexcept
{ // удалить последний

    if (size_ == 0)
        return;

    tail_->prev_ = nullptr;
    tail_ = tail_->prev_;

    --size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::insert(const_iterator fnd, const_reference obj)
{ // вставить в позицию итератора
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
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::insert(iterator fnd, value_type &&tmp)
{ // вставить временный объект --

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
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::erase(const_iterator place) noexcept
{ // удалить указанный (в позиции)
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
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::swap(List &t) noexcept
{ // обменять с заданным списком
    std::swap(size_, t.size_);
    std::swap(head_, t.head_);
    std::swap(tail_, t.tail_);
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::clear() noexcept
{ // удалить все
    clear(begin() );
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::clear(const_iterator it) noexcept
{ // удалить все начиная c позиции итератора
    auto ptr = const_cast<pointer>(it.Get() );
    while (ptr) // не хвост списка
        delete std::exchange(ptr, ptr->next_); // std::exchange возвращает old_value объекта (ptr)
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::copy(const List &obj)
{
    Node *new_obj = obj.head_;
    iterator it = begin();

    // если A < B копировать до A.size(); создать новые элементы в А после позиции A.size()
    if (size() < obj.size() )
    {
        while (it != end() )
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
    else // A > B; копировать до B.size, продолжать вставку до конца
    {
        while (new_obj != nullptr) // вставляем до конца В
        {
            *it = new_obj->data_;
            new_obj = new_obj->next_;
            ++it;
        }

        if (size() > obj.size() ) // очищаем А
        {
            tail_ = &(*it);
            clear(it); // удаляем элементы с новой позиции хвоста А
        }
    }
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::const_iterator List<T>::find(const Node &item) const noexcept
{
    for (auto it = begin(); it != end(); ++it)
        if (*it == item)
            return it;

    return const_iterator {nullptr};
}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::find(const_reference item) noexcept
{
    auto it = static_cast<const List &>(*this).find(item);
    return iterator { const_cast<pointer>(it.Get() ) };
}
//--------------------------------------------------------------------------------