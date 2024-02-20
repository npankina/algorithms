#include "Record.h"

//class Record
//----------------------------------------------------------------------
Record::Record(std::tuple<int, int, std::string, double> &&item)
: cypher_(std::get<0>(item)), year_of_pub(std::get<1>(item)), publisher(std::get<2>(item)), price_(std::get<3>(item))
{}
//----------------------------------------------------------------------
Record::Record(const Record &lvalue) // copy ctor
: cypher_(lvalue.cypher_), year_of_pub(lvalue.year_of_pub), publisher(lvalue.publisher), price_(lvalue.price_)
{}
//----------------------------------------------------------------------
Record::Record(Record &&rvalue) // move ctor
{
    cypher_ = std::move(rvalue.cypher_);
    year_of_pub = std::move(rvalue.year_of_pub);
    publisher  = std::move(rvalue.publisher);
    price_  = std::move(rvalue.price_);
}
//----------------------------------------------------------------------
Record &Record::operator=(const Record &lvalue) // copy assign
{
    if (this != &lvalue)
    {
        cypher_ = lvalue.Get_cypher();
        year_of_pub = lvalue.Get_year_of_pub();
        publisher = lvalue.Get_publisher();
        price_ = lvalue.Get_price_();
    }

    return *this;
}
//----------------------------------------------------------------------
Record &Record::operator=(Record &&rvalue) // move assign
{
    if (this != &rvalue)
    {
         std::swap(cypher_, rvalue.cypher_);
         std::swap(year_of_pub, rvalue.year_of_pub);
         std::swap(publisher, rvalue.publisher);
         std::swap(price_, rvalue.price_);
    }

    return *this;
}
//----------------------------------------------------------------------
bool Record::operator==(const Record &item) const noexcept
{
    return cypher_ == item.Get_cypher();
}
//----------------------------------------------------------------------
bool Record::operator!=(const Record &item) const noexcept
{
    return cypher_ != item.Get_cypher();
}
//----------------------------------------------------------------------
bool Record::operator>(const Record &item) const noexcept
{
    return price_ == item.Get_price_();
}
//----------------------------------------------------------------------
bool Record::operator<(const Record &item) const noexcept
{
    return price_ != item.Get_price_();
}
//----------------------------------------------------------------------