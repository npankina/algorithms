#include "Subcriber.h"

// class Subscriber
//--------------------------------------------------------------------------------
Subscriber::Subscriber(std::pair<std::string, int> item)
: last_name(item.first), taken_books(item.second), sub_cypher(tool::subscribers_cypher++), lib_data(0)
{}
//--------------------------------------------------------------------------------
Subscriber::Subscriber(const Subscriber &lhs)
: last_name(lhs.last_name), taken_books(lhs.taken_books), sub_cypher(lhs.sub_cypher)
{
     lib_data = lhs.lib_data; // вызовется copy ctor для List
}
//--------------------------------------------------------------------------------
Subscriber::Subscriber(Subscriber &&rhs)
: last_name(std::move(rhs.last_name)), taken_books(std::move(rhs.taken_books)), sub_cypher(std::move(rhs.sub_cypher))
{
    lib_data = std::move(rhs.lib_data);
}
//--------------------------------------------------------------------------------
Subscriber &Subscriber::operator=(const Subscriber &lhs)
{
    if (&lhs != this)
    {
        last_name = lhs.last_name;
        taken_books = lhs.taken_books;
        sub_cypher = lhs.sub_cypher;
        lib_data = lhs.lib_data;
    }
    return *this;
}
//--------------------------------------------------------------------------------
Subscriber &Subscriber::operator=(Subscriber &&rhs)
{
    if (&rhs != this)
    {
        std::swap(last_name, rhs.last_name);
        std::swap(taken_books, rhs.taken_books);
        std::swap(sub_cypher, rhs.sub_cypher);
        lib_data.swap(rhs.lib_data);
    }
    return *this;
}
//--------------------------------------------------------------------------------
void Subscriber::add_book(Record &&item)
{
    lib_data.push_back(item);
}
//--------------------------------------------------------------------------------
void Subscriber::replace_book(Record &fnd, Record &&replace)
{
    List::iterator it = lib_data.find(fnd);
    lib_data.insert(it, replace); // вставить перед искомым элементом
    lib_data.erase(++it); // передвинуть итератор и удалить старый элемент
}
//--------------------------------------------------------------------------------
void Subscriber::delete_book(Record &item)
{
    List::iterator it = lib_data.find(item);
    lib_data.erase(it);
}
//--------------------------------------------------------------------------------
bool Subscriber::search_by_cypher(int fnd)
{
    List::iterator it = lib_data.begin();
    while (it != lib_data.end() )
    {
        if ((*it).data_.Get_cypher() == fnd)
            return true;
        it++;
    }
    return false;
}
//--------------------------------------------------------------------------------
bool Subscriber::search_by_price(double fnd)
{
    List::iterator it = lib_data.begin();
    while (it != lib_data.end() )
    {
        if ((*it).data_.Get_price_() == fnd)
            return true;
        it++;
    }
    return false;
}
//--------------------------------------------------------------------------------