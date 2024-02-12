#ifndef LAB_2_LIST_H
#define LAB_2_LIST_H

#include <iostream>
#include <iterator>
#include <utility>
#include "../Data_Classes/Record.h"

template <typename T, typename Alloc = std::allocator<T> >
class List
{
public:
    struct Node
    {
        Node *prev_; // TODO заменить на smart pointer STL
        Node *next_; // TODO заменить на smart pointer STL
        T data_;

        Node(T item) noexcept;
        Node(const Node &lhs); // copy ctor
        Node(Node &&rhs); // move ctor
        Node &operator=(const Node &lhs); // copy assign
        Node &operator=(Node &&rhs) noexcept; // move assign
        bool operator==(const Node &item) const noexcept;
    }; // end of Node class

    // Usings
    using value_type = Node;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = Node *; // TODO заменить на smart pointer STL
    using const_pointer = const Node *; // TODO заменить на smart pointer STL
    using reference = Node &;
    using const_reference = const Node &;

    class Const_Iterator
    {
    private:
        friend class List;
        explicit Const_Iterator(const Node *ptr) noexcept; // TODO заменить на smart pointer STL

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
        const Node *Get() const noexcept; // TODO заменить на smart pointer STL

        const Node *current_; // TODO заменить на smart pointer STL
    };  // -- конец const-итератора --

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

        Iterator() : Const_Iterator() {};
        explicit Iterator(Node *ptr) noexcept; // TODO заменить на smart pointer STL
        reference operator*() const noexcept;
        Iterator &operator++() noexcept;
        Iterator &operator--() noexcept;
        Iterator operator++(int) noexcept;
        Iterator operator--(int) noexcept;
    };  // -- конец итератора --


    using iterator = Iterator;
    using const_iterator = Const_Iterator;


    /* Конструкторы/деструктор/присваивания */
    List(int size = 0);
    List(const std::initializer_list<value_type> &items);
    List(const List &other) noexcept;          // copy ctor
    List(List &&other) noexcept;              // move ctor
    List &operator=(List &&other) noexcept; // move assign
    List &operator=(const List &other);     // copy assign
    ~List();

    // Итераторы ----------------
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    iterator begin() noexcept;
    iterator end() noexcept;
    iterator find(const_reference item) noexcept;
    const_iterator find(const Node &item) const noexcept;
    // Доступ к элементам -------
    reference front();
    reference back();
    // Размеры ------------------
    bool empty() const noexcept;
    size_type size() const noexcept;
    // Модификаторы контейнера --
    void push_front(const_reference rhs);        // добавить в начало
    void push_front(value_type &&tmp);          // добавить в начало - временный объект --
    void pop_front() noexcept;               // удалить первый
    void push_back(const_reference obj);         // добавить в конец
    void push_back(value_type &&tmp);           // добавить в начало - временный объект --
    void pop_back() noexcept;                         // удалить последний
    void insert(const_iterator fnd, const_reference obj);  // вставить в позицию итератора
    void insert(iterator fnd, value_type &&tmp);     // вставить временный объект --
    void erase(const_iterator place) noexcept;                    // удалить указанный (в позиции)
    void swap(List &t) noexcept;        // обменять с заданным списком
    void clear() noexcept;                                // удалить все
    void clear(const_iterator it) noexcept; // удалить все начиная c позиции итератора

    friend std::ostream &operator<<(std::ostream &os, List &items);

private:
    void copy(const List &obj);

    // -- структура элемента списка
    size_type size_;
    pointer head_;
    pointer tail_;
};
//--------------------------------------------------------------------------------
#endif //LAB_2_LIST_H
