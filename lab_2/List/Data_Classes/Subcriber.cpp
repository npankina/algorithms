#include "Subcriber.h"

// class Subscriber
//--------------------------------------------------------------------------------
Subscriber::Subscriber(std::string name)
: last_name(name), taken_books(0), sub_cypher(tool::subscribers_cypher++)
{}
//--------------------------------------------------------------------------------
Subscriber::Subscriber(const Subscriber &lhs)
: last_name(lhs.last_name), taken_books(lhs.taken_books), sub_cypher(lhs.sub_cypher)
{
     lib_data = lhs.lib_data; // вызовется copy ctor
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
void Subscriber::Get_Lib_Data()
{
    std::cout << lib_data << std::endl;
}
//--------------------------------------------------------------------------------
void Subscriber::Set_Name(std::string name)
{
    last_name = name;
}
//--------------------------------------------------------------------------------
void Subscriber::add_book(Record &&item)
{
    lib_data.push_back(item);
    ++taken_books;
}
//--------------------------------------------------------------------------------
int Subscriber::Get_First_Element_ID()
{
    return (*lib_data.begin() ).data_.Get_cypher();
}
//--------------------------------------------------------------------------------
bool Subscriber::replace_book(const Record fnd, Record &&replace)
{
    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
    {
        if ( (*it).data_.Get_publisher() == fnd.Get_publisher() )
        {
            lib_data.erase(it); // удалить старый элемент
            lib_data.push_front(replace);
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------------------------
bool Subscriber::delete_book(const Record item)
{
    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
    {
        if ( (*it).data_.Get_publisher() == item.Get_publisher() )
        {
            lib_data.erase(it);
            --taken_books;
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------------------------
bool Subscriber::search_by_cypher(int item)
{
    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
        if ( (*it).data_.Get_cypher() == item)
            return true;
    return false;
}
//--------------------------------------------------------------------------------
bool Subscriber::search_by_price(double fnd)
{
    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
        if ( (*it).data_.Get_price_() == fnd)
            return true;
    return false;
}
//--------------------------------------------------------------------------------