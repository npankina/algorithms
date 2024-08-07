/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#pragma once
#include "List.h"
#include "Record.h"

//--------------------------------------------------------------------------------
namespace tool
{
    static int subscribers_cypher = 10000;
}
//--------------------------------------------------------------------------------
class Subscriber
{
public:
    Subscriber(std::string name = "");
    Subscriber(const Subscriber &lvalue); // copy ctor
    Subscriber(Subscriber &&rvalue); // move ctor
    Subscriber &operator=(const Subscriber &lvalue); // copy assign
    Subscriber &operator=(Subscriber &&rvalue); // move assign

    void Get_Lib_Data();
    int Get_Taken_Books() { return taken_books; }
    std::string Get_Name() { return last_name; }
    int Get_First_Element_ID();
    void Set_Name(std::string name);

    void add_book(Record &&item);
    bool replace_book(const Record find, Record &&replace);
    bool delete_book(const Record item);
    bool search_by_cypher(int fnd);
    bool search_by_price(double fnd);

private:
    static const int size = 10;

    List<Record> lib_data; // данные о взятых книгах
    std::string last_name;
    int taken_books; // количество полученных книг
    int sub_cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------