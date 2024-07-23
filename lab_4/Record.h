/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#pragma once
#include <iostream>
#include <string>
#include <tuple>

//--------------------------------------------------------------------------------
namespace tool
{
    static int cypher = 10000000;
}
//--------------------------------------------------------------------------------
class Record
{
public:
    Record(std::tuple<int, std::string, double> &&item);
    Record(std::tuple<int, int, std::string, double> &&item);
    Record(int c, int i, std::string s, double d);
    Record(const Record &lvalue); // copy ctor
    Record(Record &&rvalue); // move ctor
    Record &operator=(const Record &lvalue); // copy assign
    Record &operator=(Record &&rvalue); // move assign
    bool operator==(const Record &item) const noexcept;

    int Get_cypher() const { return cypher_; }
    int Get_year_of_pub() const { return year_of_pub; }
    std::string Get_publisher() const { return publisher; }
    double Get_price_() const { return price_; }

private:
    int cypher_;
    int year_of_pub;
    std::string publisher;
    double price_;
};