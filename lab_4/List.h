#ifndef LAB_4_LIST_H
#define LAB_4_LIST_H


#include <iostream>
#include <string>
#include <tuple>
#include <iterator>
#include <type_traits>
#include <list>

class Node
{
public:
    std::tuple<std::string, int, std::string> data_;
    Node *prev_;
    Node *next_;
};


class List
{
public:
    // -- типы – определить самостоятельно --
    using size_type = size_t;
    using value_type = Node;
    using reference = value_type &;
    using const_reference = const value_type &;

private:
    // -- структура элемента списка – определить самостоятельно --
    Node **head_;
    Node **tail_;
    size_type size_;

public:
    // -- Вложенный класс-итератор –
    struct iterator
    {   // Конструкторы --
        explicit iterator(Node *t) noexcept;
        iterator() noexcept;
        // Сравнение итераторов
        bool operator==(const iterator &it) const noexcept;
        bool operator!=(const iterator &it) const noexcept;
        // Перемещение итератора
        iterator& operator++();             // вперед
        iterator& operator--();             // назад
        reference operator*();              // разыменование
    };  // -- конец итератора --

    /* Конструкторы/деструктор/присваивания */
    List();
    virtual ~List();
    List(const std::initializer_list<value_type> &t);
    List(const List& other);
    List(List&& other) noexcept;              // -- конструктор переноса --
    List& operator=(List&& other) noexcept;   // -- операция перемещания --
    List& operator=(const List& other);
// Итераторы ----------------
    iterator begin() noexcept;
    iterator end() noexcept;
// Доступ к элементам -------
    reference front();
    reference back();
// Размеры ------------------
    bool empty () const noexcept;
    size_type size() const noexcept;
// Модификаторы контейнера --
    void push_front (const_reference);        // добавить в начало
    void push_front (value_type &&);          // добавить в начало - временный объект --
    void pop_front ();                        // удалить первый
    void push_back (const_reference);         // добавить в конец
    void push_back (value_type &&);           // добавить в начало - временный объект --
    void pop_back ();                         // удалить последний
    iterator insert (iterator, const_reference);  // вставить в позицию итератора
    iterator insert (iterator, value_type&&);     // вставить временный объект --
    iterator erase (iterator);                    // удалить указанный (в позиции)
    void clear ();                                // удалить все
    void swap (List &t) noexcept;        // обменять с заданным списком
};

#endif //LAB_4_LIST_H
