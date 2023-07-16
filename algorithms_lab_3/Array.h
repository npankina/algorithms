#ifndef ALGORITHMS_LAB_3_ARRAY_H
#define ALGORITHMS_LAB_3_ARRAY_H

#pragma once

#include <algorithm>
#include <initializer_list>
#include <tuple>
#include <algorithm>
#include <iostream>
//#include "Config.h"

// интерфейс хранилища данных
struct Record
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

// интерфейс контейнера
class Array : private Record
{
public:
    using size_type = size_t;
    using value_type = Record;
    using iterator = value_type *;
    using const_iterator = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

private:
    size_type allocated_;
    size_type size_;
    value_type *data_ = nullptr;

public:
    Array();
    explicit Array(const size_type &alloc_size);
    Array(const std::initializer_list<value_type> &t);
    Array(const Array &other);                // copy ctor
    Array(Array &&other) noexcept;            // move ctor
    Array &operator=(const Array &other);     // copy assign
    Array &operator=(Array &&other) noexcept; // move assign
    virtual ~Array() noexcept;

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

    // аллокация памяти
    void realloc(size_type new_capacity);

    // -- методы-модификаторы
    void push_back(const value_type &value);
    void pop_back() noexcept;
    void push_front(const value_type &value);
    void pop_front() noexcept;   // удалить первый элемент
    void insert(size_type indx); // -- вставить елемент перед элементом idx
    void insert(iterator it);    // -- вставить елемент перед элементом it
    void erase(size_type indx);  // -- удалить элемент idx
    void erase(iterator it);

    void clear() noexcept;
    void swap(Array &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Array &rhs);
};
#endif //ALGORITHMS_LAB_3_ARRAY_H