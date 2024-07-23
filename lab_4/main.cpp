/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#include <list>
#include <algorithm>
#include <chrono>
#include "List.h"

template<typename V, typename R>
std::ostream& operator<<(std::ostream &s, const std::chrono::duration<V,R> &d)
{
    s << d.count();
    return s;
}

int main() {
    setlocale(LC_ALL, "UTF-8");

    srand(time(NULL));

    std::cout << "Лабораторная работа #4. Двусвязный список" << std::endl;

    const size_t LIST_SIZE = 10'000'000;
    std::cout << "Размер контейнера = " << LIST_SIZE << '\n' << std::endl;

    std::cout << "**************************************************" << std::endl;
    // 0. Заполнить контейнер случайными данными.
    //--------------------------------------------------
    List A;

    std::cout << "Вывод результатов работы контейнера List\n";
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < LIST_SIZE; ++i)
        A.push_back(Record(std::make_tuple(2021, "A", 1.25) ) );

    auto finish = std::chrono::steady_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "Алгоритм `Заполнения контейнера случайными данными` выполнен за ";
    std::chrono::minutes min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    std::chrono::seconds ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(t % std::chrono::seconds(1));
    std::cout << min << " min " << ss << " sec " << ms << " ms" << std::endl;

    {
        std::cout << "\nВывод результатов работы STL контейнера std::list\n";
        std::list<Record> B;
        start = std::chrono::steady_clock::now();

        for (int i = 0; i < LIST_SIZE; ++i)
            B.push_back(Record(std::make_tuple(2021, "A", 1.25) ) );

        finish = std::chrono::steady_clock::now();
        t = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

        std::cout << "Алгоритм `Заполнения контейнера случайными данными` выполнен за ";
        min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
        ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
        ms = duration_cast<std::chrono::milliseconds>(t % std::chrono::seconds(1));
        std::cout << min << " min " << ss << " sec " << ms << " ms" << std::endl;
    }

    std::cout << "\n**************************************************" << std::endl;
    // случайно переставить элементы
    //--------------------------------------------------
    std::cout << "Вывод результатов работы контейнера List: случайно переставить элементы\n";
    start = std::chrono::steady_clock::now();

    A.shuffle_elements();

    finish = std::chrono::steady_clock::now();
    t = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "Алгоритм `Cлучайно переставить элементы` выполнен за ";
    min = duration_cast<std::chrono::minutes>(t % std::chrono::hours(1));
    ss = duration_cast<std::chrono::seconds>(t % std::chrono::minutes(1));
    ms = duration_cast<std::chrono::milliseconds>(t % std::chrono::seconds(1));
    std::cout << min << " min " << ss << " sec " << ms << " ms" << std::endl;

    return 0;
}
