#include "List.h"


// class Subscriber
//--------------------------------------------------------------------------------
Subscriber::Subscriber(std::string name, int t_books, int s_cypher)
: last_name(name), taken_books(t_books), sub_cypher(s_cypher)
{}
//--------------------------------------------------------------------------------




//class Record
//----------------------------------------------------------------------
Record::Record(int cypher, int year, std::string pub, double price)
: cypher_(cypher), year_of_pub(year), publisher(pub), price_(price)
{}
//----------------------------------------------------------------------
Record::Record(const Record &lvalue)
: cypher_(lvalue.cypher_), year_of_pub(lvalue.year_of_pub), publisher(lvalue.publisher), price_(lvalue.price_)
{}
//----------------------------------------------------------------------
Record::Record(Record &&rvalue)
{}
//----------------------------------------------------------------------
Record &Record::operator=(const Record &lvalue) // copy assign
{}
//----------------------------------------------------------------------
Record &Record::operator=(Record &&rvalue) // move assign
{}
//----------------------------------------------------------------------




// class Node
//----------------------------------------------------------------------
Node::Node()
: data_(Subscriber()), prev_(nullptr), next_(nullptr)
{}
//----------------------------------------------------------------------
Node::Node(const Subscriber &lvalue, Node *prev, Node *next) // copy ctor
: data_(lvalue), prev_(prev), next_(next)
{}
//----------------------------------------------------------------------
Node::Node(Subscriber &&rvalue, Node *prev, Node *next) // move ctor
: data_(std::move(rvalue)), prev_(prev), next_(next) // перемещаю данные rvalue, указатели выставляю в nullptr - ими манипулирует List
{}
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
    iterator copy(*this);
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
    Node *new_node = new Node(std::move(tmp.data_)); // создаю новую Node и перемещаю данные rvalue

    new_node->prev_ = head_;
    new_node->next_ = head_->next_;
    head_->next_ = new_node;
    new_node->next_->prev_ = new_node->next_;

    ++size_;
}
//----------------------------------------------------------------------
void List::pop_front()
{ // удалить первый
    if (head_->next_ == tail_) // список пуст
        return;

    head_->next_ = head_->next_->next_; // ссылка на ноду 2
    head_->next_->next_ = head_; // ссылка в ноде 2 на начало

    --size_;
}
//----------------------------------------------------------------------
void List::push_back(const_reference obj)
{ // добавить в конец
    Node *new_nd = new Node(obj.data_); // создан новый объект Node<T> в куче

    // перекинуть ссылки в элементах
    new_nd->next_ = tail_; // current_nd
    new_nd->prev_ = tail_->prev_;
    tail_->prev_->next_ = new_nd; // prev_nd
    tail_->prev_ = new_nd; // next_nd

    ++size_;
}
//----------------------------------------------------------------------
void List::push_back(value_type &&tmp)
{ // добавить в начало - временный объект --
    Node *new_nd = new Node(std::move(tmp.data_));

    new_nd->next_ = tail_;
    new_nd->prev_ = tail_->prev_;
    tail_->prev_->next_ = new_nd;
    tail_->prev_ = new_nd;

    ++size_;
}
//----------------------------------------------------------------------
void List::pop_back()
{ // удалить последний
    if ( tail_->prev_ == head_) // список пуст
        return;

    tail_->prev_ = tail_->prev_->prev_;
    tail_->prev_->prev_ = tail_;

    --size_;
}
//----------------------------------------------------------------------
List::iterator List::insert(iterator fnd, const_reference obj)
{ // вставить в позицию итератора
    for (auto it = begin(); it != end(); it++)
    {
        if (it == fnd)
        {
            Node *new_obj = new Node(obj);
            Node *current_nd = new Node(*it);
            Node *next_nd = it.ptr_;
            ++it;

            current_nd->next_ = new_obj;
            next_nd->prev_ = new_obj;
            new_obj->prev_ = current_nd;
            new_obj->next_ = next_nd;
            return it;
            ++size_;
        }
    }
    return iterator(); // nullptr
}
//----------------------------------------------------------------------
List::iterator List::insert(iterator fnd, value_type &&tmp)
{  // вставить временный объект --
    for (auto it = begin(); it != end(); it++) // перебираем в цикле все объекты в контейнере
    {
        if (it == fnd) // если искомый объект нашелся
        {
            Node *new_obj = new Node(std::move(tmp)); // создать новую ноду и переместить в нее обхект rvalue
            Node *current_nd = new Node(*it); //
            Node *next_nd = it.ptr_;
            ++it;

            current_nd->next_ = new_obj;
            next_nd->prev_ = new_obj;
            new_obj->prev_ = current_nd;
            new_obj->next_ = next_nd;
            return it;
            ++size_;
        }
    }
    return iterator(); // nullptr
}
//----------------------------------------------------------------------
List::iterator List::erase(iterator)
{ // удалить указанный (в позиции)

}
//----------------------------------------------------------------------
void List::clear()
{ // удалить все
    size_ = 0;
    head_->next_ = tail_;
    tail_->prev_ = head_;
}
//----------------------------------------------------------------------
void List::swap(List &t) noexcept
{
    std::swap(*this, t);
}
//----------------------------------------------------------------------