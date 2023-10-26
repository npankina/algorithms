#ifndef LAB_4_SUBCRIBER_H
#define LAB_4_SUBCRIBER_H

#pragma once
#include "List.h"

//--------------------------------------------------------------------------------
namespace tool
{
    static int subscribers_cypher = 10000;
}
//--------------------------------------------------------------------------------
class Subscriber
{
public:
    Subscriber(std::pair<std::string, int> item);
    Subscriber(const Subscriber &lvalue); // copy ctor
    Subscriber(Subscriber &&rvalue); // move ctor
    Subscriber &operator=(const Subscriber &lvalue); // copy assign
    Subscriber &operator=(Subscriber &&rvalue); // move assign

    void add_book(Record &&item);
    void replace_book(Record &find, Record &&replace);
    void delete_book(Record &item);
    bool search_by_cypher(int fnd);
    bool search_by_price(double fnd);

private:
    static const int size = 10;

    List lib_data; // данные о взятых книгах
    std::string last_name;
    int taken_books; // количество полученных книг
    int sub_cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------
#endif //LAB_4_SUBCRIBER_H