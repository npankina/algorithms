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
    explicit Subscriber(std::string name = "", int t_books = 0, int s_cypher = tool::subscribers_cypher++);

//    Subscriber(const Subscriber &lvalue); // copy ctor
//    Subscriber(Subscriber &&rvalue); // move ctor
//    Subscriber &operator=(const Subscriber &lvalue); // copy assign
//    Subscriber &operator=(Subscriber &&rvalue); // move assign

    void add_book();
    void replace_book();
    void delete_book();
    void search_by_book_cypher();
    void search_by_price();

private:
    static const int size = 10;

    List lib_data; // данные о взятых книгах
    std::string last_name;
    int taken_books; // количество полученных книг
    int sub_cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------
#endif //LAB_4_SUBCRIBER_H