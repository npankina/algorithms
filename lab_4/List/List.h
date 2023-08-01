#ifndef LAB_4_LIST_H
#define LAB_4_LIST_H

#include <iostream>
#include <tuple>
#include <iterator>
#include <string>


class List
{
public:
    struct Node
    {
        std::tuple<std::string, size_t, std::string, std::string, double> data_;
        Node *prev;
        Node *next;
    };

    using size_type = size_t;
    using value_type = Node;
    using reference = value_type &;
    using const_reference = const value_type &;

    struct iterator
    {
    public:
        explicit iterator(List::Node *t) noexcept;
        iterator() noexcept;
        bool operator==(const iterator &it) const noexcept;
        bool operator!=(const iterator &it) const noexcept;
        iterator &operator++();
        iterator &operator--();
        reference operator*();
        value_type *operator->();
    private:
        value_type *ptr_;
        size_t size_;
    };

    List();
    virtual ~List();
    List(const std::initializer_list <value_type> &t);
    List(const List &other);
    List(List &&other) noexcept;
    List &operator=(List &&other) noexcept;
    List &operator=(const List &other);

// Итераторы ----------------
    iterator begin() const noexcept;
    iterator end() const noexcept;

// Доступ к элементам -------
    reference front();
    reference back();

// Размеры ------------------
    bool empty() const noexcept;
    size_type size() const noexcept;

// Модификаторы контейнера --
    void push_front(const_reference);        // добавить в начало
    void push_front(value_type &&);          // добавить в начало - временный объект --
    void pop_front();                        // удалить первый
    void push_back(const_reference);         // добавить в конец
    void push_back(value_type &&);           // добавить в начало - временный объект --
    void pop_back();                         // удалить последний
    iterator insert(iterator, const_reference);  // вставить в позицию итератора
    iterator insert(iterator, value_type &&);     // вставить временный объект --
    iterator erase(iterator);                    // удалить указанный (в позиции)
    void clear();                                // удалить все
    void swap(List &t) noexcept;        // обменять с заданным списком

private:
    Node *data_;
    Node *head_;
    Node *tail_;

    size_t size_;
    iterator it;
};

#endif //LAB_4_LIST_H