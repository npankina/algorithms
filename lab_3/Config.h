#include <vector>
#include <string>

struct Record // интерфейс хранилища данных
{ //    std::tuple<std::string, int, std::string, std::string, double>
    size_t bookId_;
    size_t yearOfPub_;
    std::string bookName_;
    std::string publisher_;
    double price_;

    Record(size_t year = 0, std::string name = "", std::string pub = "", double price = .0);

private:
    static size_t counter;
};

std::vector<Record> rec
{
        {2020, "C++ programming", "Pearson", 9.99},
        {2019, "Databases", "Pearson", 8.75},
        {2017, "Postgres", "Thomson-Reuters", 3.12},
        {2010, "C++ with Love", "Thomson-Reuters", 5.70},
        {2023, "Algorithms and data structures", "Oxford University", 7.24},
        {2023, "C++ the best lang", "Pearson", 4.99},
        {2022, "C++ 💜", "Pearson", 5.00},
        {2020, "Algorithms in C++", "Oxford University", 4.20},
        {2021, "Data structures in C++", "Oxford University", 5.18},
        {2015, "Project Management", "Pearson", 5.22}
};