#include "List.h"
#include <algorithm>
#include <random>


//----------------------------------------------------------------------
int random_number(int from, int to)
{
    int num = from + rand() % to;
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


int main() {
    std::cout << "Лабораторная работа #4. Двусвязный список" << std::endl;

    const size_t LIST_SIZE = 5;
    std::cout << "Размер контейнера = " << LIST_SIZE << '\n' << std::endl;

    // 0. Заполнить контейнер случайными данными.
    //--------------------------------------------------
    List A(LIST_SIZE);
    auto start = std::chrono::steady_clock::now();
    std::generate(A.begin(), A.end(), fill_list_cont);
    auto finish = std::chrono::steady_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "Алгоритм `Заполнения контейнера случайными данными` выполнен за ";
    std::chrono::minutes min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    std::chrono::seconds ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(t % std::chrono::seconds (1));
    std::cout << min << " min " << ss << " sec " << ms << " ms" << std::endl;

    std::cout << A.size() << std::endl;

    return 0;
}
