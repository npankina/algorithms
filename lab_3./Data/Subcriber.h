/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#pragma once
#include <iostream>
#include "Record.h"
#include "../List.hpp"

//--------------------------------------------------------------------------------
template <typename Cont = List<Record> >
class Subscriber
{
public:
    Subscriber(std::string name);
    Subscriber(const Subscriber &lvalue); // copy ctor
    Subscriber(Subscriber &&rvalue); // move ctor
    Subscriber &operator=(const Subscriber &lvalue); // copy assign
    Subscriber &operator=(Subscriber &&rvalue); // move assign

    void Get_Lib_Data();
    int Get_Cyper() { return Cypher; }
    int Get_Taken_Books() { return Taken_Books; }
    std::string Get_Name() { return Name; }
    void Set_Name(std::string name);

    void Add_Book(const Record &item);
    void Replace_Book(const int index, const Record &replace);
    void Delete_Book(Record &item);
    bool Search_By_Cypher(const int fnd) const;
    bool Search_By_Price(const double fnd) const;

    friend std::ostream &operator<<(std::ostream &os, Cont &cont);

private:
    Cont Cont_Lib_Data;
    std::string Name;
    int Taken_Books;
    int Cypher;
};
//--------------------------------------------------------------------------------