#ifndef LAB_4_LIST_H
#define LAB_4_LIST_H


#include <iostream>
#include <string>
#include <tuple>
#include <iterator>
#include <type_traits>
#include <list>

template <typename U>
class Node
{
public:
    U data_;
    Node *prev_ = nullptr;
    Node *next_ = nullptr;

    Node(Node *prev, const U &&value, Node *next) // move ctor
    {
        data_ = std::move(value);
        if (prev == nullptr or next == nullptr) // выбросить исключение nullptr
            throw std::exception();
    }
    Node(Node *prev, const U &value, Node *next) : prev_(prev), data_(value), next_(next) {}; // copy ctor
    Node(Node *prev, Node *next) : prev_(prev), next_(next) {};

};

template <typename T>
class List
{
public:
    // -- типы – определить самостоятельно --
    using size_type = size_t;
    using value_type = Node<T>;
    using reference = value_type &;
    using const_reference = const value_type &;

private:
    // -- структура элемента списка – определить самостоятельно --
    size_type size_;
    value_type *tail_;
    value_type *head_;

public:
    // -- Вложенный класс-итератор –
    struct iterator : public std::iterator<std::bidirectional_iterator_tag, Node<T>, size_type, Node<T> *, T>
    {
    private:
        friend class List;
//        friend class const_iterator;
    public:
        typename iterator::pointer ptr;

        explicit iterator(value_type *t) noexcept;
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
