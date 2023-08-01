#include "List.h"

List::iterator::iterator(Node *t) noexcept
{

}
//--------------------------------------------------
List::iterator::iterator() noexcept
{

}
//--------------------------------------------------
bool List::iterator::operator==(const iterator &it) const noexcept
{

}
//--------------------------------------------------
bool List::iterator::operator!=(const iterator &it) const noexcept
{

}
//--------------------------------------------------
List::iterator &List::iterator::operator++()
{
    ++ptr_;
    return *this;
}
//--------------------------------------------------
List::iterator &List::iterator::operator--()
{
    --ptr_;
    return *this;
}
//--------------------------------------------------
List::reference List::iterator::operator*()
{
    return *ptr_;
}
//--------------------------------------------------
List::value_type *List::iterator::operator->()
{
    return ptr_;
}
//--------------------------------------------------
List::List()
: data_(nullptr), size_(0)
{}
//--------------------------------------------------
List::~List()
{

}
//--------------------------------------------------
List::List(const std::initializer_list <value_type> &t)
{

}
//--------------------------------------------------
List::List(const List &other)
{

}
//--------------------------------------------------
List::List(List &&other) noexcept
{

}
//--------------------------------------------------
List &List::operator=(List &&other) noexcept
{

}
//--------------------------------------------------
List &List::operator=(const List &other)
{

}
//--------------------------------------------------
List::iterator List::begin() const noexcept
{
    return iterator(data_);
}
//--------------------------------------------------
List::iterator List::end() const noexcept
{
    return iterator(data_ + size_);
}
//--------------------------------------------------
List::reference List::front()
{
    return *(head_);
}
//--------------------------------------------------
List::reference List::back()
{
    return *(tail_);
}
//--------------------------------------------------
bool List::empty() const noexcept
{
    return size_ == 0;
}
//--------------------------------------------------
List::size_type List::size() const noexcept
{
    return size_;
}
//--------------------------------------------------
void List::push_front(const_reference)
{ // добавить в начало

}
//--------------------------------------------------
void List::push_front(value_type &&)
{ // добавить в начало - временный объект --

}
//--------------------------------------------------
void List::pop_front()
{ // удалить первый

}
//--------------------------------------------------
void List::push_back(const_reference)
{ // добавить в конец

}
//--------------------------------------------------
void List::push_back(value_type &&)
{ // добавить в начало - временный объект --

}
//--------------------------------------------------
void List::pop_back()
{ // удалить последний

}
//--------------------------------------------------
List::iterator List::insert(iterator, const_reference)
{ // вставить в позицию итератора

}
//--------------------------------------------------
List::iterator List::insert(iterator, value_type &&)
{ // вставить временный объект --

}
//--------------------------------------------------
List::iterator List::erase(iterator)
{ // удалить указанный (в позиции)

}
//--------------------------------------------------
void List::clear()
{ // удалить все

}
//--------------------------------------------------
void List::swap(List &t) noexcept
{ // обменять с заданным списком

}
//--------------------------------------------------
