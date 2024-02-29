#pragma once
#include <iostream>
#include <iterator>
#include <utility>
#include <memory>

/*
*    Управление динамической памятью:
*        – перегрузить операции new/delete для класса List;
*        – использовать стандартный аллокатор (распределитель памяти);
*/

template <typename T, typename Alloc = std::allocator<T> >
class List
{
private:
    template <typename U>
    class Node
    {
    public:
        Node() = delete;
        Node(U item) noexcept : prev_(nullptr), next_(nullptr), data_{ std::move(item) } {};
        Node(const Node &rhs) noexcept : prev_(rhs.prev_), next_(rhs.next_), data_(rhs.data_) {}; // copy ctor
        Node(Node &&other) noexcept : prev_{ std::move(other.prev_)}, next_{ std::move(other.next_)}, data_{ std::move(other.data_)} {}; // move ctor

        Node *prev_;
        Node *next_;
        U data_;
    }; // end of Node class

public:
    // Usings
    using value_type = Node<T>;
    using reference = Node<T> &;
    using const_reference = const Node<T> &;
    using pointer = Node<T> *;
    using const_pointer = const Node<T> *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    class Const_Iterator
    {
    private:
        friend class List;
        explicit Const_Iterator(const Node<T> *ptr) noexcept;

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
        const Node<T> *Get() const noexcept;

        const Node<T> *current_;
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
        explicit Iterator(Node<T> *ptr) noexcept;
        reference operator*() const noexcept;
        Iterator &operator++() noexcept;
        Iterator &operator--() noexcept;
        Iterator operator++(int) noexcept;
        Iterator operator--(int) noexcept;
    };  // end of Iterator class

    using iterator = Iterator;
    using const_iterator = Const_Iterator;

    List(const T &value = T(), const Alloc &alloc = Alloc() );
    List(const std::initializer_list<value_type> &items, const T &value = T(), const Alloc &alloc = Alloc());
    List(const List &other) noexcept;          // copy ctor
    List(List &&other) noexcept;              // move ctor
    List &operator=(List &&other) noexcept; // move assign
    List &operator=(const List &other);     // copy assign
    ~List();

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
    void insert(const size_type index, const T &replace);
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
    void clear(const_iterator it) noexcept;

    using AllocTraits = std::allocator_traits<Alloc>;
//    std::allocator_traits<Alloc>::rebind_alloc<Node<T> >;

    Node<T> *head_;
    Node<T> *tail_;
    size_type size_;
    AllocTraits  alloc_;

};
//--------------------------------------------------------------------------------