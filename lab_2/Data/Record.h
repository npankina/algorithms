#pragma once
#include <iostream>
#include <string>
#include <tuple>

//--------------------------------------------------------------------------------
namespace tool
{
    static int cypher = 10000000;
    static int subscribers_cypher = 10000;
    static const int Max_taken_books_size = 50;
}
//--------------------------------------------------------------------------------
class Record
{
public:
    Record() = delete;
    explicit Record(std::tuple<int, int, std::string, double> &&item);

    Record(const Record &lvalue); // copy ctor
    Record(Record &&rvalue); // move ctor
    Record &operator=(const Record &lvalue); // copy assign
    Record &operator=(Record &&rvalue); // move assign

    bool operator==(const Record &item) const noexcept;
    bool operator!=(const Record &item) const noexcept;
    bool operator>(const Record &item) const noexcept;
    bool operator<(const Record &item) const noexcept;

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
//--------------------------------------------------------------------------------