#pragma once
#include "Array.h"

size_t random_number(size_t min, size_t max)
{
    size_t num = min + rand() % (max - min + 1);
    std::cout << "Rand number = " << num << " ";
    return num;
}
//--------------------------------------------------
bool Fill_Container(Array &obj, size_t size)
{
    srand(time(NULL)); // установка seed длф ГСП

    for (size_t i = 0; i < size; ++i)
        obj.push_back(rec[random_number(0, 9)]);
    return obj.size() == size;
}
//--------------------------------------------------
