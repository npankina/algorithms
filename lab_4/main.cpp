#include "List.h"
#include <algorithm>
#include <list>



int main() {
    setlocale(LC_ALL, "UTF-8");
#if wrong
    srand(time(NULL));

    std::cout << "Лабораторная работа #4. Двусвязный список" << std::endl;

    const size_t LIST_SIZE = 10; //'000'000;
    std::cout << "Размер контейнера = " << LIST_SIZE << '\n' << std::endl;

    // 0. Заполнить контейнер случайными данными.
    //--------------------------------------------------
    List A;
    std::cout << "Вывод результатов работы контейнера List\n";
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < LIST_SIZE; ++i)
        A.push_back(fill_list_cont() );

    auto finish = std::chrono::steady_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "Алгоритм `Заполнения контейнера случайными данными` выполнен за ";
    std::chrono::minutes min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    std::chrono::seconds ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(t % std::chrono::seconds (1));
    std::cout << min << " min " << ss << " sec " << ms << " ms" << std::endl;

//    std::cout << A.size() << std::endl;
    std::cout << "List A BEFORE shuffle" << std::endl;
    std::cout << A << std::endl;
    A.Shuffle_Elements();

    std::cout << "List A AFTER shuffle" << std::endl;
    std::cout << A << std::endl;

#if list
    std::cout << "\nВывод результатов работы STL контейнера std::list\n";
    std::list<Record> B;
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < LIST_SIZE; ++i)
        B.push_back(fill_list_cont() );

    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "Алгоритм `Заполнения контейнера случайными данными` выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    ms = duration_cast<std::chrono::milliseconds>(t % std::chrono::seconds (1));
    std::cout << min << " min " << ss << " sec " << ms << " ms" << std::endl;

//    std::cout << A << std::endl;

    std::cout << "**************************************************" << std::endl;
#endif
#endif

    List A;
    A.push_back(Record{std::make_tuple(2021, "A", 1.25)});
    A.push_back(Record{std::make_tuple(2020, "Bekly", 2.39)});
    A.push_back(Record{std::make_tuple(2022, "B", 2.25)});

    std::cout << "List A Before shuffle" << std::endl;
    std::cout << A << std::endl;
    A.Shuffle_Elements();

    std::cout << "List A AFTER shuffle" << std::endl;
    std::cout << A << std::endl;

    return 0;
}
