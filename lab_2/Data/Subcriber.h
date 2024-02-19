#pragma once
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
    std::string Get_Name() { return Name; }
    int Get_First_Element_ID();
    void Set_Name(std::string name);

    void Add_Book(Record &&item);
    bool Replace_Book(const Record find, Record &&replace);
    bool Delete_Book(const Record item);
    bool Search_By_Cypher(int fnd);
    bool Search_By_Price(double fnd);

private:
    Cont Cont_Lib_Data;
    std::string Name;
    int Taken_Books; // количество полученных книг
    int Cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------