#ifndef LAB_4_RECORD_H
#define LAB_4_RECORD_H

#pragma once
#include <string>
#include <tuple>

//--------------------------------------------------------------------------------
namespace tool
{
    static int cypher = 10000000;
}
//--------------------------------------------------------------------------------
class Record
{
public:
    Record(std::tuple<int, std::string, double> &&item);
    Record(const Record &lvalue); // copy ctor
    Record(Record &&rvalue); // move ctor
    Record &operator=(const Record &lvalue); // copy assign
    Record &operator=(Record &&rvalue); // move assign
    bool operator==(const Record &item) const noexcept;

    int Get_cypher() { return cypher_; }
    int Get_year_of_pub() { return year_of_pub; }
    std::string Get_publisher() { return publisher; }
    double Get_price_() { return price_; }

private:
    int cypher_;
    int year_of_pub;
    std::string publisher;
    double price_;
};
#endif //LAB_4_RECORD_H
