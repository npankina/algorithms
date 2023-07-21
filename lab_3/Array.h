#ifndef ALGORITHMS_LAB_3_ARRAY_H
#define ALGORITHMS_LAB_3_ARRAY_H

#pragma once

#include <iostream>
#include <initializer_list>
#include <cstdlib>
#include <algorithm>
#include "Config.h"


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

    size_t Linear_Search_with_barier(int value);
    int Linear_Search(size_t key, std::string index);
    int Linear_Search(std::string key, std::string index);


    friend std::ostream &operator<<(std::ostream &os, const Array &rhs);

private:
    void realloc(size_type new_capacity); // аллокация памяти

    size_type allocated_;
    size_type size_;
    value_type *data_ = nullptr;
//    iterator iterator_ = data_;
};
#endif //ALGORITHMS_LAB_3_ARRAY_H