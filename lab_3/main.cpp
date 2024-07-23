/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#include "Array.h"

//--------------------------------------------------
template<typename V, typename R>
std::ostream& operator<<(std::ostream &s, const std::chrono::duration<V,R> &d)
{
    s << d.count();
    return s;
}
//--------------------------------------------------
bool interp_search(std::vector<int> &obj, int target);


int main()
{
    const size_t ARRAY_SIZE = 1000000;
    std::cout << "Размер контейнера = " << ARRAY_SIZE << '\n' << std::endl;

    // 0. Заполнить контейнер случайными данными.
    //--------------------------------------------------
    Array A;
    auto start = std::chrono::steady_clock::now();
    Fill_Container_1(A, ARRAY_SIZE);
    auto finish = std::chrono::steady_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `Заполнения контейнера случайными данными` выполнен за ";
    std::chrono::minutes min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    std::chrono::seconds ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec" << std::endl;

    //--------------------------------------------------
    std::vector<int> B;
    start = std::chrono::steady_clock::now();
    Fill_Container_2(B, ARRAY_SIZE);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `Заполнения контейнера случайными данными` для vector выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t% std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec\n" << std::endl;

#if need
    // 1. Реализовать алгоритм последовательного поиска с барьером по неупорядоченному контейнеру.
    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    A.linear_search_with_barier(2020);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `поиска в неупорядоченном массиве` выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec" << std::endl;


    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    auto res = find(B.begin(), B.end(), 9);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `поиска в неупорядоченном массиве` для vector выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t% std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec\n" << std::endl;
#endif

    // 2.0 Сортировка
    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    A.selection_sort(2020);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `сортировки` выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec" << std::endl;

    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    sort(B.begin(), B.end());
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `сортировки` для vector выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t% std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec\n" << std::endl;

#if need
    // 2.1 Реализовать алгоритм последовательного поиска с барьером по упорядоченному контейнеру.
    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    A.linear_search_with_barier(2022);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `поиска в упорядоченном массиве` выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec" << std::endl;

    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    auto res = find(B.begin(), B.end(), 9);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `поиска в упорядоченном массиве` для vector выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec\n" << std::endl;
#endif

    // 3.1 Бинарный поиск
    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    A.binary_search(2023);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `бинарный поиск` выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec" << std::endl;

    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    auto ress = std::binary_search(B.begin(), B.end(), 19);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `бинарный поиск` для vector выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec\n" << std::endl;


    // 3.2 Интерполяционный поиск
    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    A.interpolation_serch(2019);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `интерполяционный поиск` выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec" << std::endl;


    //--------------------------------------------------
    start = std::chrono::steady_clock::now();
    interp_search(B, 22);
    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

    std::cout << "Алгоритм `интерполяционный поиск` для vector выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::cout << min << " min " << ss << " sec" << std::endl;
    //--------------------------------------------------

    return 0;
}

bool interp_search(std::vector<int> &obj, int target)
{
    int min = 0, max = obj.size() - 1, pos = 0;
    while (min <= max)
    {
        pos = min + (((target - obj[min]) * (max - min) ) / (obj[max] - obj[min]) );

        if (pos < 0)
            return false;

        if (obj[pos] == target)
            return true;
        else if (obj[pos] < target)
            min = pos + 1;
        else
            max = pos - 1;
    }
    return false;
}