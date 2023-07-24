#pragma once

#include <iostream>
#include <initializer_list>
#include <cstdlib>
#include <algorithm>
#include <chrono>


struct Record // интерфейс хранилища данных
{
    size_t bookId_;
    size_t yearOfPub_;
    std::string bookName_;
    std::string publisher_;
    double price_;

    Record(size_t year = 0, std::string name = "", std::string pub = "", double price = .0);

private:
    static size_t counter;
};


//std::vector<Record> rec
//{
//        {2016, "C++ programming", "Pearson", 9.99},
//        {2019, "Databases", "Pearson", 8.75},
//        {2017, "Postgres", "Thomson-Reuters", 3.12},
//        {2010, "C++ with Love", "Thomson-Reuters", 5.70},
//        {2018, "Algorithms and data structures", "Oxford University", 7.24},
//        {2023, "C++ the best lang", "Pearson", 4.99},
//        {2022, "C++ 💜", "Pearson", 5.00},
//        {2020, "Algorithms in C++", "Oxford University", 4.20},
//        {2021, "Data structures in C++", "Oxford University", 5.18},
//        {2015, "Project Management", "Pearson", 5.22}
//};

class Array : private Record // интерфейс контейнера
{
public:
    using size_type = size_t;
    using value_type = Record;
    using iterator = value_type *;
    using const_iterator = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    Array();
    explicit Array(const size_type &alloc_size);
    Array(const std::initializer_list<value_type> &t);
    Array(const Array &other);                // copy ctor
    Array(Array &&other) noexcept;            // move ctor
    Array &operator=(const Array &other);     // copy assign
    Array &operator=(Array &&other) noexcept; // move assign
    virtual ~Array() noexcept;

    bool operator==(const Array &rhs) const;
    bool operator!=(const Array &rhs) const;

    size_type size() const noexcept;
    bool empty() const noexcept;
    size_type capacity() const noexcept;
    // -- iterators
    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator cend() const noexcept;
    // -- доступ к элементам
    reference operator[](size_type);
    const_reference operator[](size_type) const;
    reference front() noexcept;
    const_reference front() const noexcept;
    reference back() noexcept;
    const_reference back() const noexcept;
    bool at(size_t idx) const noexcept;
    // -- методы-модификаторы
    void push_back(const value_type &value);
    void pop_back() noexcept;
    void push_front(const value_type &value);
    void pop_front() noexcept;   // удалить первый элемент
    void insert(size_type index, value_type &&value); // -- вставить елемент перед элементом idx
    void insert(iterator it, value_type &&value); // вставить элемент перед элементом it
    void erase(size_type idx);  // -- удалить элемент idx

    void clear() noexcept;
    void swap(Array &rhs);

    // Алгоритм последовательного поиска с барьером
    size_t linear_search_with_barier(int value);
    int linear_search(size_t key, std::string index);
    int linear_search(std::string key, std::string index = "");

    // Сортировка выбором
    void selection_sort(int x);
    void selection_sort(double x);
    bool binary_search(int target); // by year_of_pub
    bool binary_search(double target); // by price
    bool interpolation_serch(int target); // by year_of_pub
    bool interpolation_serch(double target); // by price

    friend std::ostream &operator<<(std::ostream &os, const Array &rhs);

private:
    void realloc(size_type new_capacity); // аллокация памяти

    size_type allocated_;
    size_type size_;
    value_type *data_ = nullptr;
};

size_t random_number(size_t min, size_t max);
double random_number_d(double min, double max);
bool Fill_Container(Array &obj, size_t size);
void Fill_Container_1(Array &obj, size_t arr_sz);
void Fill_Container_2(std::vector<Record> &obj, size_t arr_sz);