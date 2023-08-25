#ifndef LAB_4_LIST_H
#define LAB_4_LIST_H


#include <iostream>
#include <string>
#include <tuple>
#include <iterator>
#include <type_traits>
#include <list>


template <class U>
class Node
{
    U value_; // std::tuple<std::string, size_t, std::string, std::string, double> data_;
    Node *prev_; // std::unique_ptr<Node>
    Node *next_; // std::unique_ptr<Node>
};

template <class T> // , class Alloc = allocator<T>
class List
{
public:
    using size_type = size_t;
    using value_type = Node<T>;
    // using iterator = value_type *; using const_iterator = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    template <typename Iter>
    class Iterator
    {
        friend class List; // имеем полный доступ к классу и приватным методам
    public:
        typedef Iter iterator_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef iterator_type value_type;
        typedef ptrdiff_t difference_type;
        typedef iterator_type &reference;
        typedef iterator_type *pointer;

        iterator_type *value_;

    private:
        //  explicit Iterator(Node *t) noexcept;
        explicit Iterator(Iter *p) noexcept;
    public:
        Iterator(const Iter &it); // copy ctor
        bool operator==(const Iterator &it) const noexcept;
        bool operator!=(const Iterator &it) const noexcept;
        Iterator &operator++();
        Iterator &operator--();
        reference operator*();
    };

    typedef Iterator<Node<T>> iterator;                // для дружбы со стандартными алгоритмами
    typedef Iterator<const Node<T>> const_iterator;    // для дружбы со стандартными алгоритмами

private:
    value_type *head_;
    value_type *tail_;

    size_t size_;

public:
    List(); //noexcept(std::is_nothrow_default_constructible<allocator_type>::value);
    virtual ~List();
    List(const std::initializer_list <value_type> &t);
    List(const List &other);
    List(List &&other) noexcept;
    List &operator=(List &&other) noexcept;
    List &operator=(const List &other);

    // --- iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    // --- доступ к элементам
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // --- размеры
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    // Модификаторы контейнера --
    void push_front(const_reference);           // добавить в начало
    void push_front(value_type &&);             // добавить в начало - временный объект --
    void pop_front();                           // удалить первый
    void push_back(const_reference);            // добавить в конец
    void push_back(value_type &&);              // добавить в начало - временный объект --
    void pop_back();                            // удалить последний
    iterator insert(iterator, const_reference); // вставить в позицию итератора
    iterator insert(iterator, value_type &&);   // вставить временный объект --
    iterator erase(iterator pos);               // удалить указанный (в позиции)
    void clear() noexcept;                      // удалить все
    void swap(List &t); // noexcept(std::allocator_traits<allocator_type>::is_always_equal::value); // обменять с заданным списком
};

#endif //LAB_4_LIST_H
