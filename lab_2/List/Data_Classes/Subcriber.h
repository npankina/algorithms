#pragma once
#include "Record.h"
#include "../Array/Array.h"

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

    Array<Record> lib_data;
    std::string last_name;
    int taken_books; // количество полученных книг
    int sub_cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------