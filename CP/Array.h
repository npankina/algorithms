/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#pragma once

#include <iostream>
#include <cstdlib>
#include <initializer_list>
#include <memory>
#include <cassert>

template <typename T, typename Alloc = std::allocator<T>>
class Array
{
public:
    using size_type = size_t;
    using value_type = T;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;
    using difference_type = ptrdiff_t;


    Array();
    explicit Array(const size_type &n, const T &value = T(), const Alloc &alloc = Alloc() );
    Array(const std::initializer_list<value_type> &t, const T &value = T(), const Alloc &alloc = Alloc() );
    Array(const Array &rhs); // copy ctor
    Array(Array &&other) noexcept; // move ctor
    Array& operator=(const Array &other); // copy assign
    Array& operator=(Array &&other) noexcept; // move assign
    virtual ~Array() noexcept;

    class Const_Iterator
    {
    private:
        friend class Array;
        explicit Const_Iterator(const value_type *ptr) noexcept : current_(ptr) {};

    public:
        using difference_type = Array::difference_type;
        using value_type = Array::value_type;
        using pointer = Array::const_pointer;
        using reference = Array::const_reference;
        using iterator_category = std::bidirectional_iterator_tag;

        Const_Iterator() : current_(nullptr) {};
        reference operator*() const noexcept
        {
            return *current_;
        }
        Const_Iterator &operator++() noexcept
        {
            current_ = current_ + 1;
            return *this;
        }
        Const_Iterator &operator--() noexcept
        {
            current_ = current_ - 1;
            return *this;
        }
        Const_Iterator operator++(int) noexcept
        {
            Const_Iterator copy = *this;
            current_ = current_ + 1;
            return copy;
        }
        Const_Iterator operator--(int) noexcept
        {
            Const_Iterator copy = *this;
            current_ -= 1;
            return copy;
        }
        bool operator==(Const_Iterator rhs) const noexcept
        {
            return current_ == rhs.current_;
        }
        bool operator!=(Const_Iterator rhs) const noexcept
        {
            return !(*this == rhs);
        }

    protected:
        const value_type *Get() const noexcept
        {
            return current_;
        }

        const value_type *current_;
    };   // -- end of class Const_Iterator

    class Iterator : public Const_Iterator
    {
    private:
        friend class Array;

    public:
        using difference_type = Array::difference_type;
        using value_type = Array::value_type;
        using pointer = Array::pointer;
        using reference = Array::reference;
        using iterator_category = std::random_access_iterator_tag;

        Iterator() : Const_Iterator() {};
        explicit Iterator(value_type *ptr) noexcept;
        reference operator*() const noexcept;
        Iterator &operator++() noexcept;
        Iterator &operator--() noexcept;
        Iterator operator++(int) noexcept;
        Iterator operator--(int) noexcept;
    };  // -- end of class Iterator

    using iterator = Iterator;
    using const_iterator = Const_Iterator;


    size_type size() const noexcept;
    bool empty() const noexcept;
    size_type capacity() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;

    reference operator[](size_type);
    const_reference operator[](size_type) const;
    reference front() const noexcept;
    reference back() noexcept;
    const_reference back() const noexcept;

    void push_back(const value_type &rhs);
    void pop_back();
    void push_front(const value_type &rhs);
    void pop_front();
    void Insert(size_type index, value_type &&value);
    void insert(iterator it, value_type &&value);
    void erase(size_type index);
    void erase(iterator it);

    void swap(Array &rhs);

    friend std::ostream &operator<<(std::ostream &os, Array<T> &cont);

private:
    void clear() noexcept;
    void realloc(size_type new_capacity);

    using AllocTraits = std::allocator_traits<Alloc>;

    size_type size_;
    size_type capacity_;
    value_type *data_;
    Alloc alloc_;
};