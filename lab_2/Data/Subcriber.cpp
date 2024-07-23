/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#include "Subcriber.h"


// class Subscriber
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont>::Subscriber(std::string name)
: Cypher(tool::subscribers_cypher++), Taken_Books(0), Name(name), Cont_Lib_Data()
{}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont>::Subscriber(const Subscriber &lvalue) // copy ctor
: Cypher(lvalue.Cypher), Taken_Books(lvalue.Taken_Books), Name(lvalue.Name), Cont_Lib_Data(lvalue.Cont_Lib_Data)
{}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont>::Subscriber(Subscriber &&rvalue) // move ctor
: Cypher(std::move(rvalue.Cypher)), Taken_Books(std::move(rvalue.Taken_Books)),
  Name(std::move(rvalue.Name)), Cont_Lib_Data(std::move(rvalue.Cont_Lib_Data))
{}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont> &Subscriber<Cont>::operator=(const Subscriber &lvalue) // copy assign
{
    if (this != &lvalue)
    {
       Cypher = lvalue.Cypher;
       Taken_Books = lvalue.Taken_Books;
       Name = lvalue.Name;
       Cont_Lib_Data = lvalue.Cont_Lib_Data;
    }
    return *this;
}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont> &Subscriber<Cont>::operator=(Subscriber &&rvalue) // move assign
{
    if (this != &rvalue)
    {
        Cypher = std::move(rvalue.Cypher);
        Taken_Books = std::move(rvalue.Taken_Books);
        Name = std::move(rvalue.Name);
        Cont_Lib_Data = std::move(rvalue.Cont_Lib_Data);
    }
    return *this;
}
//--------------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Get_Lib_Data()
{
    std::cout << Cont_Lib_Data << std::endl;
}
//-----------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Set_Name(std::string name)
{
    Name = name;
}
//--------------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Add_Book(const Record &item)
{
    Cont_Lib_Data.push_back(item);
    ++Taken_Books;
}
//--------------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Replace_Book(const int index, const Record &replace)
{
   Cont_Lib_Data.insert(index, replace);
}
//--------------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Delete_Book(Record &item)
{
    Cont_Lib_Data.erase(item);
    --Taken_Books;
}
//--------------------------------------------------------------------------------
template <typename Cont>
bool Subscriber<Cont>::Search_By_Cypher(const int fnd) const
{
    if (fnd < 10000000)
        return false;

    for (auto it = Cont_Lib_Data.begin(); it != Cont_Lib_Data.end(); it++)
        if ( (*it).data_.Get_cypher() == fnd)
            return true;

    return false;
}
//--------------------------------------------------------------------------------
template <typename Cont>
bool Subscriber<Cont>::Search_By_Price(const double fnd) const
{
    for (auto it = Cont_Lib_Data.begin(); it != Cont_Lib_Data.end(); it++)
        if ( (*it).data_.Get_Price() == fnd)
            return true;

    return false;
}
//--------------------------------------------------------------------------------