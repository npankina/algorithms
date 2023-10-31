#ifndef LAB_4_FUNCTIONS_H
#define LAB_4_FUNCTIONS_H

#include <random>
#include <ctime>

//----------------------------------------------------------------------
int random_number(int from, int to)
{
    // Получить случайное число - формула
    int num = from + rand() % (from - to + 1);
    return num;
}
//----------------------------------------------------------------------
namespace strings
{
    std::vector<std::string> Lib =
            {"Berkly", "Donovan", "Jason", "Pearson", "Melon"};
}
std::string random_string()
{
    std::string str = strings::Lib[random_number(0, strings::Lib.size() )];
    return str;
}
//----------------------------------------------------------------------
Record fill_list_cont()
{
//    return Record(std::make_tuple(2023, "Pearson", 1.99));

    return Record(std::make_tuple(random_number(2010, 2023), random_string(), 0.9 + (double)random_number(1, 30)));
}
//----------------------------------------------------------------------
template<typename V, typename R>
std::ostream& operator<<(std::ostream &s, const std::chrono::duration<V,R> &d)
{
    s << d.count();
    return s;
}
//----------------------------------------------------------------------


#endif //LAB_4_FUNCTIONS_H
