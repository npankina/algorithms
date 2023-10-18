#include "List.h"


// class Subscriber
//--------------------------------------------------------------------------------
Subscriber::Subscriber(std::string name, int t_books, int s_cypher)
: last_name(name), taken_books(t_books), sub_cypher(s_cypher)
{}
//--------------------------------------------------------------------------------




//class Record
//----------------------------------------------------------------------
Record::Record(std::tuple<int, std::string, double> &&item)
: cypher_(tool::cypher++), year_of_pub(std::get<0>(item)), publisher(std::get<1>(item)), price_(std::get<2>(item))
{}
//----------------------------------------------------------------------
Record::Record(const Record &lvalue)
: cypher_(lvalue.cypher_), year_of_pub(lvalue.year_of_pub), publisher(lvalue.publisher), price_(lvalue.price_)
{}
//----------------------------------------------------------------------
Record::Record(Record &&rvalue)
{
    cypher_ = std::move(rvalue.cypher_); // ????
    std::swap(year_of_pub, rvalue.year_of_pub); // ????
    std::swap(publisher, rvalue.publisher);
    std::swap(price_, rvalue.price_);
}
//----------------------------------------------------------------------
Record &Record::operator=(const Record &lvalue) // copy assign
{
    cypher_ = lvalue.cypher_;
    year_of_pub = lvalue.year_of_pub;
    publisher = lvalue.publisher;
    price_ = lvalue.price_;
}
//----------------------------------------------------------------------
Record &Record::operator=(Record &&rvalue) // move assign
{}
//----------------------------------------------------------------------
bool Record::operator==(const Record &item) const noexcept
{
    return cypher_ == item.cypher_;
}
//----------------------------------------------------------------------




// class Node
//----------------------------------------------------------------------
List::Node::Node(Record item) noexcept
: data_{ std::move(item) }
{}
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
    return current_->data_;
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
    auto &&res = Const_Iterator::operator*();
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
    return List::Iterator {const_cast<Node *>(res.Get() ) };
}
//----------------------------------------------------------------------
List::Iterator List::Iterator::operator--(int) noexcept
{
    auto res = Const_Iterator::operator--(0);
    return Iterator {const_cast<Node *>(res.Get() ) };
}
//----------------------------------------------------------------------




// class List
//----------------------------------------------------------------------
List::List()
: size_(0), head_(nullptr), tail_(nullptr)
{}
//----------------------------------------------------------------------
List::List(const std::initializer_list<value_type> &items)
{
    for (auto &item : items)
        push_back(item);
}
//----------------------------------------------------------------------
List::List(const List &other) noexcept // copy ctor
: size_(other.size_), head_(nullptr), tail_(nullptr)
{
    for (auto &item : other)
        push_back(item);
}
//----------------------------------------------------------------------
List::List(List &&other) noexcept // move ctor
: size_(other.size_), head_(std::move(other.head_) ), tail_(std::move(other.tail_) )
{ // производим обнуление старого объекта
    other.size_ = 0;
    other.head_ = nullptr;
    other.tail_ = nullptr;
}
//----------------------------------------------------------------------
List &List::operator=(const List &other) // copy assign
{
    if (this != &other)
    {
        size_ = other.size_;
        head_ = other.head_;
        tail_ = other.tail_;
    }
    return *this;
}
//----------------------------------------------------------------------
List &List::operator=(List &&other) noexcept // move assign
{
    if (this != &other)
    {
        size_ = other.size_;
        head_ = std::move(other.head_);
        tail_ = std::move(other.tail_);

        // производим обнуление старого объекта
        other.size_ = 0;
        other.head_ = nullptr;
        other.tail_ = nullptr;
    }
    return *this;
}
//----------------------------------------------------------------------
List::~List()
{ // пройти по всей цепочке и удалить каждую Node
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
    return const_iterator(tail_);
}
List::const_iterator List::cbegin() const noexcept
{
    return const_iterator(head_);
}
//----------------------------------------------------------------------
List::const_iterator List::cend() const noexcept
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
    auto new_node = new Node(rhs);

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
    auto new_node = new Node(std::move(tmp) ); // создаю новую Node и перемещаю данные rvalue
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
    auto new_node = new Node(obj); // создан новый объект Node<T> в куче

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
    auto new_node = new Node(std::move(tmp) );
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
void List::pop_back()
{ // удалить последний
    if ( tail_ == head_) // список пуст
        return;

    tail_->prev_ = tail_->prev_->prev_;
    tail_->prev_->prev_ = tail_;

    --size_;
}
//----------------------------------------------------------------------
void List::insert(const_iterator fnd, const_reference obj)
{ // вставить в позицию итератора
    auto ptr = const_cast<pointer>(fnd.Get() );
    if (!ptr)
    {
        push_back(std::move(obj));
        return;
    }

    auto new_node = new value_type { std::move(obj) };
    new_node->next_ = ptr;
    new_node->prev_ = ptr->prev_;

    if (ptr->prev_)
        ptr->prev_->next_ = new_node;

    ptr->prev_ = new_node;
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
List::Iterator List::insert(iterator fnd, value_type &&tmp)
{  // вставить временный объект --
}
//----------------------------------------------------------------------
List::Iterator List::erase(const_iterator place) noexcept
{ // удалить указанный (в позиции)
    auto ptr = const_cast<pointer>(place.Get() );
    if (ptr->prev_)
        ptr->prev_->next_ = ptr->next_;
    else
        head_ = ptr->next_;

    if (ptr->next_)
        ptr->next_->prev_ = ptr->prev_;
    else
        tail_ = ptr->prev_;

    delete ptr;
    --size_;

    // !!!
//    return ;
}
//----------------------------------------------------------------------
void List::clear() noexcept
{
    while(tail_)
        delete std::exchange(head_, head_->next_);
    tail_ = nullptr;
    size_ = 0;
}
//----------------------------------------------------------------------
void List::swap(List &t) noexcept
{
    std::swap(*this, t);
}
//----------------------------------------------------------------------