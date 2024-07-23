/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#include "Record.h"

//class Record
//----------------------------------------------------------------------
Record::Record(std::tuple<int, std::string, double> &&item)
: cypher_(tool::cypher++), year_of_pub(std::get<0>(item)), publisher(std::get<1>(item)), price_(std::get<2>(item))
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
        price_ = lvalue.Get_Price();
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
bool Record::operator==(const double check) const noexcept
{
    // сравнение double с точностью до машинной эпсилон
    if (std::abs(price_ - check) < std::numeric_limits<double>::epsilon() )
        return true;
    return false;
}
//----------------------------------------------------------------------
bool Record::operator==(const int check) const noexcept
{
    if (price_ == check)
        return true;
    return false;
}
//----------------------------------------------------------------------