/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */

#include "Book.h"

Book::Book(const key_t &k, int year, const std::string &publisher, double price)
: key_(k), data_(std::make_tuple(year, publisher, price))
{
    if (key_.length() != Max_Simbols_Name)
        throw std::invalid_argument("Book key must be 8 characters long.");
}
//----------------------------------------------------------------------------------------------------
Book::key_t Book::Get_Id() const
{ return key_; }
//----------------------------------------------------------------------------------------------------
int Book::Get_Year() const
{
    return std::get<0>(data_);
}
//----------------------------------------------------------------------------------------------------
std::string Book::Get_Publisher() const
{
    return std::get<1>(data_);
}
//----------------------------------------------------------------------------------------------------
double Book::Get_Price() const
{
    return std::get<2>(data_);
}
//----------------------------------------------------------------------------------------------------
void Book::Set_Year(int year)
{
    std::get<0>(data_) = year;
}
//----------------------------------------------------------------------------------------------------
void Book::Set_Publisher(const std::string& publisher)
{
    std::get<1>(data_) = publisher;
}
//----------------------------------------------------------------------------------------------------
void Book::Set_Price(double price)
{
    std::get<2>(data_) = price;
}
//----------------------------------------------------------------------------------------------------
void Book::Print() const
{
    std::cout << "Key: " << key_ << ", Year: " << Get_Year()
              << ", Publisher: " << Get_Publisher()
              << ", Price: " << Get_Price()
    << std::endl;
}
//----------------------------------------------------------------------------------------------------