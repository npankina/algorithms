#pragma once

#include <iostream>
#include <iterator>
#include <utility>
#include <list>


template <typename T>
class List
{
private:
    class Node
    {
    public:
        Node() = delete;
        Node(T item) noexcept : prev_(nullptr), next_(nullptr), data_{ std::move(item) } {};

        Node *prev_;
        Node *next_;
        T data_;
    }; // end of Node class

public:
    // Usings
    using value_type = Node;
    using reference = Node &;
    using const_reference = const Node &;
    using pointer = Node *;
    using const_pointer = const Node *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    class Const_Iterator
    {
    private:
        friend class List;
        explicit Const_Iterator(const Node *ptr) noexcept;

    public:
        using difference_type = List::difference_type;
        using value_type = List::value_type;
        using pointer = List::const_pointer;
        using reference = List::const_reference;
        using iterator_category = std::bidirectional_iterator_tag;

        Const_Iterator() : current_(nullptr) {};
        reference operator*() const noexcept;
        Const_Iterator &operator++() noexcept;
        Const_Iterator &operator--() noexcept;
        Const_Iterator operator++(int) noexcept;
        Const_Iterator operator--(int) noexcept;
        bool operator==(Const_Iterator rhs) const noexcept;
        bool operator!=(Const_Iterator rhs) const noexcept;

    protected:
        const Node *Get() const noexcept;

        const Node *current_;
    };  // end of Const_Iterator class

    class Iterator : public Const_Iterator
    {
    private:
        friend class List;

    public:
        using difference_type = List::difference_type;
        using value_type = List::value_type;
        using pointer = List::pointer;
        using reference = List::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator() noexcept : Const_Iterator() {};
        explicit Iterator(Node *ptr) noexcept;
        reference operator*() const noexcept;
        Iterator &operator++() noexcept;
        Iterator &operator--() noexcept;
        Iterator operator++(int) noexcept;
        Iterator operator--(int) noexcept;
    };  // end of Iterator class

    using iterator = Iterator;
    using const_iterator = Const_Iterator;

    List();
    List(const std::initializer_list<value_type> &items);
    List(const List &other) noexcept;          // copy ctor
    List(List &&other) noexcept;              // move ctor
    List &operator=(List &&other) noexcept; // move assign
    List &operator=(const List &other);     // copy assign
    ~List();

//    reference operator[](size_type);
    T &operator[](size_type);
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    iterator begin() noexcept;
    iterator end() noexcept;
    iterator find(T &item) noexcept;
    const_iterator find(const T &item) const noexcept;
    bool is_element_exsist(const T &item);
    reference front();
    reference back();
    bool is_empty() const noexcept;
    size_type size() const noexcept;
    void push_front(const T &rhs);
    void push_front(T &&tmp);
    void pop_front() noexcept;
    void push_back(const T &obj);
    void push_back(T &&tmp);
    void pop_back() noexcept;
    void insert(T &find, const T &replace);
    bool erase(const T &item) noexcept;
    void swap(List &t) noexcept;
    void clear() noexcept;

private:
    void copy(const List &obj);
    void push_front(const_reference obj);
    void push_front(value_type &&tmp);
    void push_back(const_reference obj);
    void push_back(value_type &&tmp);
    iterator find(reference item) noexcept;
    const_iterator find(const_reference item) const noexcept;
    void erase(const_iterator place) noexcept;
    void insert(const_iterator fnd, const_reference obj);
    void insert(iterator fnd, value_type &&tmp);
    void replace(iterator fnd, T &tmp);
    void clear(const_iterator it) noexcept;


    size_type size_;
    Node *head_;
    Node *tail_;
};
//--------------------------------------------------------------------------------