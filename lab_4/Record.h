#ifndef LAB_4_RECORD_H
#define LAB_4_RECORD_H

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

private:
    int cypher_;
    int year_of_pub;
    std::string publisher;
    double price_;
};
//--------------------------------------------------------------------------------
Record Make_Tuple_for_Record(int year, std::string pub, double price)
{
    return Record(std::make_tuple(year, pub, price) );
}
//--------------------------------------------------------------------------------
#endif //LAB_4_RECORD_H
