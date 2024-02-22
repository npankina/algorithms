#pragma once
#include <iostream>
#include "Record.h"
#include "../Array/Array.h"


//--------------------------------------------------------------------------------
template <typename Cont = Array<Record> >
class Subscriber
{
public:
    Subscriber(std::string name);
    Subscriber(const Subscriber &lvalue); // copy ctor
    Subscriber(Subscriber &&rvalue); // move ctor
    Subscriber &operator=(const Subscriber &lvalue); // copy assign
    Subscriber &operator=(Subscriber &&rvalue); // move assign

    void Get_Lib_Data();
    int Get_Taken_Books() { return Taken_Books; }
    Record& Get_Book_By_Index(int n) { return Cont_Lib_Data[n]; }
    std::string Get_Name() { return Name; }
    void Set_Name(std::string name);

    void Add_Book(Record &&item);
    void Add_Book(const Record &item);
    void Replace_Book(Record &find, const Record &replace);
    void Delete_Book(const Record &item);
    bool Search_By_Cypher(int fnd);
    bool Search_By_Price(double fnd);

    friend std::ostream &operator<<(std::ostream &os, Cont &cont);

private:
    Cont Cont_Lib_Data;
    std::string Name;
    int Taken_Books; // количество полученных книг
    int Cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------