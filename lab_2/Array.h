#ifndef LAB_2_ARRAY_H
#define LAB_2_ARRAY_H

#include <iostream>
#include <cstdlib>
#include <initializer_list>

template <typename T>
class Array
{
public:
    using size_type = size_t;
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using reference = value_type& ;
    using const_reference = const value_type& ;

public:
    // -- конструкторы и присваивания --
    Array();
    explicit Array(const size_type &n, value_type t = 0);
    Array(const std::initializer_list<value_type> &t);
    Array(const Array &other);
    Array(Array &&other) noexcept;
    Array& operator=(const Array &other);
    Array& operator=(Array &&other) noexcept;
    virtual ~Array() noexcept;

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
    reference front() noexcept;
    const_reference front() const noexcept;
    reference back() noexcept;
    const_reference back() const noexcept;
    // -- методы-модификаторы
    void push_back(const value_type &v);             // -- добавить элемент в конец --
    void pop_back() noexcept;                        // удалить последний элемент
    void push_front(const value_type &v);            // -- добавить элемент в начало --
    void pop_front() noexcept;                       // удалить первый элемент
    void Insert(size_type idx);			             // -- вставить елемент перед элементом idx
    void insert(iterator it);			 	         // -- вставить елемент перед элементом it
    void erase(size_type idx); 			             // -- удалить элемент idx
    void erase(iterator it);	 			         // -- удалить элемент it

    void clear() noexcept;    	     		         // очистить массив
    void swap(Array &rhs);                           // -- обмен массивов - типа перемещения --
};

#endif //LAB_2_ARRAY_H
