#ifndef LAB_2_ARRAY_H
#define LAB_2_ARRAY_H

#include <iostream>
#include <cstdlib>
#include <initializer_list>
#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class Array
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = value_type & ;
    using const_reference = const value_type & ;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = value_type *;
    using const_iterator = const value_type *;

public:
    // -- конструкторы и присваивания --
    Array();
    explicit Array(const size_type &n, const T& value = T(), const Alloc &alloc = Alloc() );
    Array(const std::initializer_list<value_type> &t);
    Array(const Array &other); // copy ctor
    Array(Array &&other) noexcept; // move ctor
    Array& operator=(const Array &other); // copy assign
    Array& operator=(Array &&other) noexcept; // move assign
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
    void push_back(const value_type &v);              // -- добавить элемент в конец --
    void pop_back() noexcept;                         // удалить последний элемент
    void push_front(const value_type &rhs);             // -- добавить элемент в начало --
    void pop_front() noexcept;                        // удалить первый элемент
    void Insert(size_type index, value_type &&value); // -- вставить елемент перед элементом idx
    void insert(iterator it, value_type &&value);     // -- вставить елемент перед элементом it
    void erase(size_type index); 			          // -- удалить элемент idx
    void erase(iterator it);	 			          // -- удалить элемент it

    void clear() noexcept;    	     		         // очистить массив
    void swap(Array &rhs);                           // -- обмен массивов - типа перемещения --

    void realloc(size_type new_capacity);

private:
    using AllocTraits = std::allocator_traits<Alloc>;

    size_type size_;
    size_type capacity_;
    value_type *data_;
    Alloc alloc_;
};
#endif //LAB_2_ARRAY_H
