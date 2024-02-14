#pragma once
#include "Record.h"
#include "../Array.h"

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
    int Get_Taken_Books() { return Taken_Books; }
    std::string Get_Name() { return Last_Name; }
    int Get_First_Element_ID();
    void Set_Name(std::string name);

    void Add_Book(Record &&item);
    bool Replace_Book(const Record find, Record &&replace);
    bool Delete_Book(const Record item);
    bool Search_By_Cypher(int fnd);
    bool Search_By_Price(double fnd);

private:
    static const int size = 10;

    struct Node
    {
        Record lib_data;
        std::tuple<unsigned char, unsigned char, unsigned char, unsigned char> date;
        std::pair<unsigned char, unsigned char> time;
    };

    Array<Node> Library_Data;
    std::string Last_Name;
    int Taken_Books; // количество полученных книг
    int Subsciber_Cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------