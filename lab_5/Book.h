#pragma once
#include <string>
#include <tuple>
#include <stdexcept>
#include <iostream>


class Book
{
public:
    using key_t = std::string; // Шифр книги (8 символов)
    using data_t = std::tuple<int, std::string, double>; // Год издания, издательство, цена

    Book(const key_t &k, int year, const std::string &publisher, double price);

    // Геттеры
    key_t Get_Id() const;
    int Get_Year() const;
    std::string Get_Publisher() const;
    double Get_Price() const;

    // Установка новых данных
    void Set_Year(int year);
    void Set_Publisher(const std::string &publisher);
    void Set_Price(double price);

    // Вывод информации о книге
    void Print() const;

private:
    key_t key_;
    data_t data_;

    static const int Max_Simbols_Name = 8;
};