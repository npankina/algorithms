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




// class Const_Iterator
//--------------------------------------------------------------------------------
template <typename T>
List<T>::Const_Iterator::Const_Iterator(const Node *ptr) noexcept
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
List<T>::Iterator::Iterator(Node *ptr) noexcept
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
    for (auto &item : items)
        push_back(item);
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::List(const List &other) noexcept          // copy ctor
: size_(0), head_(nullptr), tail_(nullptr)
{   // (deep copy)
    for (auto &item: other)
        push_back(item);
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
//template <typename T>
//List<T>::reference List<T>::operator[](size_type index)
//{
//
//}
//--------------------------------------------------------------------------------
template <typename T>
T& List<T>::operator[](size_type index)
{
    if (index >= size_ or index < 0)
        throw std::out_of_range("Error => index out of range");

    int i = 1;
    for (auto it = begin(); it != end(); it++, i++)
        if (i == index)
            return it;
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
        head_->prev_ = new_item;
        new_item->next_ = head_;
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
        head_->prev_ = new_item;
        new_item->next_ = head_;
        head_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(const T &rhs)
{ // добавить в начало; Time Complexity: O(1)

    Node *new_item = new Node(rhs);
    if (head_) // если список > 0
    {
        head_->prev_ = new_item;
        new_item->next_ = head_;
        head_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_front(T &&tmp)
{ // добавить в начало; Time Complexity: O(1)

    Node *new_item = new Node(std::move(tmp) );
    if (head_) // если список > 0
    {
        head_->prev_ = new_item;
        new_item->next_ = head_;
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
void List<T>::push_back(value_type &&tmp)
{ // добавить в начало - временный объект --

    Node *new_item = std::move(tmp);

    if (tail_)
    {
        tail_->next_ = new_item;
        new_item->prev_ = tail_;
        tail_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(const_reference obj)
{ // добавить в конец
    Node *new_item = new Node(obj);

    if (tail_)
    {
        tail_->next_ = new_item;
        new_item->prev_ = tail_;
        tail_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(const T &obj)
{ // добавить в конец
    Node *new_item = new Node(obj);

    if (tail_)
    {
        tail_->next_ = new_item;
        new_item->prev_ = tail_;
        tail_ = new_item;
    }
    else
        head_ = tail_ = new_item;

    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::push_back(T &&temp)
{ // добавить в конец

    Node *new_item = new Node(std::move(temp));

    if (tail_)
    {
        tail_->next_ = new_item;
        new_item->prev_ = tail_;
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
void List<T>::insert(T &f, const T &replace)
{
    iterator it = find(f);
    if (*it != nullptr)
        insert(it, replace);
    else
        std::cout << "Элемент отсутствует в списке!!" << std::endl;
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

    Node *new_node = new Node(obj);
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

    Node *new_node = std::move(tmp);
    new_node->next_ = ptr;
    new_node->prev_ = ptr->prev_;

    if (ptr->prev_)
        ptr->prev_->next_ = new_node;

    ptr->prev_ = new_node;
    ++size_;
}
//--------------------------------------------------------------------------------
template <typename T>
void List<T>::replace(iterator fnd, T &tmp)
{ // вставить временный объект --

    auto ptr = const_cast<pointer>(fnd.Get() ); // снятие константности и разыменование указателя

    Node *new_node = new Node(tmp);
    new_node->next_ = ptr;
    new_node->prev_ = ptr->prev_;

    if (ptr->prev_)
        ptr->prev_->next_ = new_node;

    ptr->prev_ = new_node;
}
//--------------------------------------------------------------------------------
template <typename T>
bool List<T>::erase(const T &item) noexcept
{
    const_iterator ptr = find(item);
    if (ptr != static_cast<Const_Iterator>(nullptr))
    {
        erase(ptr);
        return true;
    }
    else
        std::cout << "Элемент не найден" << std::endl;

    return false;
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
    {
        delete std::exchange(ptr, ptr->next_); // std::exchange возвращает old_value объекта (ptr)
        --size_;
    }

    if (size_ == 0)
        head_ = tail_ = nullptr;
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
List<T>::const_iterator List<T>::find(const_reference item) const noexcept
{
    for (auto it = begin(); it != end(); ++it)
        if (*it == item)
            return it;

    return const_iterator {nullptr};
}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::find(reference item) noexcept
{
    auto it = static_cast<const List &>(*this).find(item);
    return iterator { const_cast<pointer>(it.Get() ) };
}
//--------------------------------------------------------------------------------
template <typename T>
List<T>::const_iterator List<T>::find(const T &item) const noexcept
{
    for (auto it = begin(); it != end(); it++)
        if ( (*it).data_ == item)
            return it;

    return const_iterator {nullptr};
}
//----------------------------------------------------------------------
template <typename T>
List<T>::iterator List<T>::find(T &item) noexcept
{
    auto it = static_cast<const T &>(*this).find(item);
    return iterator { const_cast<pointer>(it.Get() ) };
}
//--------------------------------------------------------------------------------
template <typename T>
bool List<T>::is_element_exsist(const T &item)
{
    for (auto it = begin(); it != end(); it++)
        if ( (*it).data_ == item)
            return true;

    return false;
}
//--------------------------------------------------------------------------------