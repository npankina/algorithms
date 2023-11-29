#ifndef LAB_1_LIST_H
#define LAB_1_LIST_H

#include <iostream>
#include <iterator>

/* OOP
 * lab #12
*/

template <typename T>
class List
{
private:
    class Node
    {
    public:
        Node(T data) : prev_(nullptr), next_(nullptr), data_(std::move(data) ) {};

    private:
        Node *prev_;
        Node *next_;
        T data_;
    };

public:
    // -- типы – определить самостоятельно --
    using size_type = size_t;
    using value_type = Node;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using difference_type = ptrdiff_t;

private:
    // -- структура элемента списка – определить самостоятельно --
    size_type size_;
    pointer *head_, *tail_;

public:
    // -- Вложенный класс-итератор –
    class Iterator
    {
    private:
        friend class List;
        explicit Iterator(const Node *ptr) noexcept;

    public:
        using difference_type = List::difference_type;
        using value_type = List::value_type;
        using pointer = List::const_pointer;
        using reference = List::const_reference;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator();
        reference operator*() const noexcept;
        Iterator &operator++() noexcept;
        Iterator &operator--() noexcept;
        Iterator operator++(int) noexcept;
        Iterator operator--(int) noexcept;
        bool operator==(Iterator rhs) const noexcept;
        bool operator!=(Iterator rhs) const noexcept;

    private:
        const Node *current_;
    };  // -- конец итератора --

    using iterator = Iterator;

    /* Конструкторы/деструктор/присваивания */
    List();
    virtual ~List();
    List(const std::initializer_list<value_type> &t);
    List(const List& other);
    List(List&& other) noexcept;              // -- конструктор переноса --
    List& operator=(List&& other) noexcept;   // -- операция перемещания --
    List& operator=(const List& other);
    // Итераторы ------------------------- -- снимать константность -- ? --
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
    void swap (List &t) noexcept;       // обменять с заданным списком
};
#endif //LAB_1_LIST_H