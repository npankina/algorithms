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

public:
    // -- конструкторы и присваивания --
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
    };  // -- конец const-итератора --
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
    };  // -- конец итератора --

    using iterator = Iterator;
    using const_iterator = Const_Iterator;

    // -- размеры --
    size_type size() const noexcept;             // текущее количество элементов
    bool empty() const noexcept;                 // есть ли элементы
    size_type capacity() const noexcept;         // потенциальный размер
    // -- итераторы -- это просто указатели --
    iterator begin() noexcept;
    iterator end() noexcept;
    // -- доступ к элементам --
    reference operator[](size_type);
    const_reference operator[](size_type) const;
    reference front() const noexcept;
    reference back() noexcept;
    const_reference back() const noexcept;
    // -- методы-модификаторы
    void push_back(const value_type &rhs);            // -- добавить элемент в конец --
    void pop_back(); //noexcept;                      // удалить последний элемент
    void push_front(const value_type &rhs);           // -- добавить элемент в начало --
    void pop_front();                                 // удалить первый элемент
    void Insert(size_type index, value_type &&value); // -- вставить елемент перед элементом idx
    void insert(iterator it, value_type &&value);     // -- вставить елемент перед элементом it
    void erase(size_type index); 			          // -- удалить элемент idx
    void erase(iterator it);	 			          // -- удалить элемент it

    void swap(Array &rhs);                           // -- обмен массивов - типа перемещения --

    friend std::ostream &operator<<(std::ostream &os, Array<T> &cont);

private:
    void clear() noexcept;    	     		         // очистить массив
    void realloc(size_type new_capacity);

    using AllocTraits = std::allocator_traits<Alloc>;

    size_type size_;
    size_type capacity_;
    value_type *data_;
    Alloc alloc_;
};