#include "List.h"

// class Node
//----------------------------------------------------------------------
List::Node::Node(Record item) noexcept
: prev_(nullptr), next_(nullptr), data_{ std::move(item) }
{}
//----------------------------------------------------------------------
List::Node::Node(const Node &lhs)
: prev_(lhs.prev_), next_(lhs.next_),
  data_{ lhs.data_.Get_cypher(),lhs.data_.Get_year_of_pub(),
         lhs.data_.Get_publisher(), lhs.data_.Get_price_() }
{}
//----------------------------------------------------------------------
List::Node::Node(Node &&rhs) // move ctor
: prev_(std::move(rhs.prev_) ), next_(std::move(rhs.next_) ),
  data_(std::move(std::make_tuple(
          rhs.data_.Get_cypher(), rhs.data_.Get_year_of_pub(),
          rhs.data_.Get_publisher(),rhs.data_.Get_price_())) )
{}
//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
bool List::Node::operator==(const_reference item) const noexcept
{
    return data_ == item.data_;
}
//----------------------------------------------------------------------




// class Const_Iterator
//----------------------------------------------------------------------
List::Const_Iterator::Const_Iterator(const value_type *ptr) noexcept
: current_(ptr)
{}
//----------------------------------------------------------------------
List::Const_Iterator::reference List::Const_Iterator::operator*() const noexcept
{
    return *current_;
}
//----------------------------------------------------------------------
List::Const_Iterator &List::Const_Iterator::operator++() noexcept
{
    current_ = current_->next_;
    return *this;
}
//----------------------------------------------------------------------
List::Const_Iterator &List::Const_Iterator::operator--() noexcept
{
    current_ = current_->prev_;
    return *this;
}
//----------------------------------------------------------------------
List::Const_Iterator List::Const_Iterator::operator++(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->next_;
    return copy;
}
//----------------------------------------------------------------------
List::Const_Iterator List::Const_Iterator::operator--(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->prev_;
    return copy;
}
//----------------------------------------------------------------------
bool List::Const_Iterator::operator==(Const_Iterator rhs) const noexcept
{
    return current_ == rhs.current_;
}
//----------------------------------------------------------------------
bool List::Const_Iterator::operator!=(Const_Iterator rhs) const noexcept
{
    return !(*this == rhs);
}
//----------------------------------------------------------------------
const List::Node *List::Const_Iterator::Get() const noexcept
{
    return current_;
}
//----------------------------------------------------------------------




// class Iterator
//----------------------------------------------------------------------
List::Iterator::Iterator(value_type *ptr) noexcept
: Const_Iterator(ptr)
{}
//----------------------------------------------------------------------
List::reference List::Iterator::operator*() const noexcept
{
    auto &&res = std::move(Const_Iterator::operator*());
    return const_cast<reference>(res);
}
//----------------------------------------------------------------------
List::Iterator &List::Iterator::operator++() noexcept
{
    Const_Iterator::operator++();
    return *this;
}
//----------------------------------------------------------------------
List::Iterator &List::Iterator::operator--() noexcept
{
    Const_Iterator::operator--();
    return *this;
}
//----------------------------------------------------------------------
List::Iterator List::Iterator::operator++(int) noexcept
{
    auto res = Const_Iterator::operator++(0);
    return List::Iterator {const_cast<pointer>(res.Get() ) };
}
//----------------------------------------------------------------------
List::Iterator List::Iterator::operator--(int) noexcept
{
    auto res = Const_Iterator::operator--(0);
    return Iterator {const_cast<pointer>(res.Get() ) };
}
//----------------------------------------------------------------------




// class List
//----------------------------------------------------------------------
List::List(int size)
: size_(size), head_(nullptr), tail_(nullptr)
{}
//----------------------------------------------------------------------
List::List(const std::initializer_list<value_type> &items)
: List()
{
    for (auto &item : items)
        push_back(item);
}
//----------------------------------------------------------------------
List::List(const List &other) noexcept // copy ctor
: List(0)
{
    copy(other);
}
//----------------------------------------------------------------------
List::List(List &&other) noexcept // move ctor
: size_(other.size_), head_(std::move(other.head_) ), tail_(std::move(other.tail_) )
{}
//----------------------------------------------------------------------
List &List::operator=(const List &other) // copy assign
{
    if (this != &other)
    {
        size_ = other.size_;
        copy(other);
    }
    return *this;
}
//----------------------------------------------------------------------
List &List::operator=(Node &&other)
{
    push_front(other);
}
//----------------------------------------------------------------------
List &List::operator=(List &&other) noexcept // move assign
{
    if (this != &other)
    {
        size_ = other.size_;
        head_ = std::move(other.head_);
        tail_ = std::move(other.tail_);
    }
    return *this;
}
//----------------------------------------------------------------------
List::~List()
{
    clear();
}
//----------------------------------------------------------------------
List::const_iterator List::begin() const noexcept
{
    return const_iterator(head_);
}
//----------------------------------------------------------------------
List::const_iterator List::end() const noexcept
{
    return const_iterator(nullptr);
}
//----------------------------------------------------------------------
List::iterator List::begin() noexcept
{
    return iterator(head_);
}
//----------------------------------------------------------------------
List::iterator List::end() noexcept
{
    return iterator(nullptr);
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
//----------------------------------------------------------------------
void List::push_front(value_type &&tmp)
{ // добавить в начало - временный объект --
    Node *new_node = new Node(std::move(tmp) ); // создаю новую Node и перемещаю данные rvalue
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
//----------------------------------------------------------------------
void List::pop_front() noexcept
{
    erase(begin() );
}
//----------------------------------------------------------------------
void List::push_back(const_reference obj)
{ // добавить в конец
    Node *new_node = new Node(obj); // создан новый объект Node<T> в куче

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
//----------------------------------------------------------------------
void List::push_back(value_type &&tmp)
{ // добавить в начало - временный объект --
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
//----------------------------------------------------------------------
void List::pop_back() noexcept
{ // удалить последний
    if ( tail_ == head_) // список пуст
        return;

    tail_->prev_ = nullptr;
    tail_ = tail_->prev_;

    --size_;
}
//----------------------------------------------------------------------
void List::insert(const_iterator fnd, const_reference obj)
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
//----------------------------------------------------------------------
void List::insert(iterator fnd, value_type &&tmp)
{  // вставить временный объект --
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
//----------------------------------------------------------------------
void List::erase(const_iterator place) noexcept
{ // удалить указанный (в позиции) элемент
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
//----------------------------------------------------------------------
void List::clear() noexcept
{ // пройти по всей цепочке и удалить каждую Node
    while (head_)
        delete std::exchange(head_, head_->next_);
    head_ = tail_ = nullptr;
    size_ = 0;
}
//----------------------------------------------------------------------
void List::clear(const_iterator it) noexcept
{
    auto ptr = const_cast<pointer>(it.Get() );
    while (ptr) // не хвост списка
        delete std::exchange(ptr, ptr->next_);
}
//----------------------------------------------------------------------
void List::swap(List &t) noexcept
{ // обменять с заданным списком
    std::swap(size_, t.size_);
    std::swap(head_, t.head_);
    std::swap(tail_, t.tail_);
}
//----------------------------------------------------------------------
void List::copy(const List &obj)
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
//----------------------------------------------------------------------
List::const_iterator List::find(const Node &item) const noexcept
{
    for (auto it = begin(); it != end(); ++it)
        if (*it == item)
            return it;

    return const_iterator {nullptr};
}
//----------------------------------------------------------------------
List::iterator List::find(const_reference item) noexcept
{
    auto it = static_cast<const List &>(*this).find(item);
    return iterator { const_cast<pointer>(it.Get() ) };
}
//----------------------------------------------------------------------
void List::shuffle_elements()
{
    List a, b;
    split(a, b);

    a.append(b);
    head_ = std::move(a.head_);

    a.head_ = a.tail_ = nullptr;
    a.size_ = 0;
}
//--------------------------------------------------------------------------------
void List::append(List &b)
{
    tail_->next_ = b.head_;
    tail_->next_->prev_ = tail_;
    tail_ = b.tail_;

    b.head_ = b.tail_ = nullptr;
    b.size_ = 0;
}
//--------------------------------------------------------------------------------
void List::split(List &a, List &b)
{
    bool flag = true;

    for (List::iterator it = begin(); it != end(); it++)
    {
        auto &&temp = (*it).data_;
        if (flag)
        {
            a.push_front(temp);
            flag = false;
        }
        else
        {
            b.push_front(temp);
            flag = true;
        }
    }
}
//--------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, List &list)
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
void List::merge_sort()
{   /* Реализовать алгоритм сортировки слиянием
     * разделить список на 2 части
     * рекурсивно сортировать обе части
     */
    
    // 1. функция - разделяющая список на 2 части
    List a, b;
    split(a, b);
    
    // 2. рекурсивный вызов сортировки
    sort(a, b);
    
    // 3. слить 2 списка в один (заменив текущий)
    a.append(b);
    head_ = a.head_;
}
//--------------------------------------------------------------------------------
void List::sort(List &a, List &b)
{
    iterator a_it = a.begin();
    iterator b_it = b.begin();
    
    while ((*a_it).next_ != nullptr)
    {
        
    }
}