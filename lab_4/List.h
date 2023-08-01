#ifndef LAB_4_LIST_H
#define LAB_4_LIST_H


#include <iostream>
#include <string>
#include <tuple>
#include <iterator>
#include <type_traits>


template <typename T>
class List
{
public:
    struct Node
    {
        T value; // std::tuple<std::string, size_t, std::string, std::string, double> data_;
        Node *prev; // std::unique_ptr<Node>
        Node *next; // std::unique_ptr<Node>
    };

    using size_type = size_t;
    using value_type = Node;
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
//        explicit Iterator(Node *t) noexcept;
        explicit Iterator(Iter *p) noexcept;
    public:
        Iterator(const Iter &it); // copy ctor
        bool operator==(const Iterator &it) const noexcept;
        bool operator!=(const Iterator &it) const noexcept;
        Iterator &operator++();
        Iterator &operator--();
        reference operator*();
    };

    List();
    virtual ~List();
    List(const std::initializer_list <value_type> &t);
    List(const List &other);
    List(List &&other) noexcept;
    List &operator=(List &&other) noexcept;
    List &operator=(const List &other);

// Итераторы ----------------
    typedef Iterator<Node> iterator; // для дружбы со стандартными алгоритмами
    typedef Iterator<const Node> const_iterator; // для дружбы со стандартными алгоритмами

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const;
    const_iterator end() const;

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
    iterator erase(iterator pos);                    // удалить указанный (в позиции)
    void clear();                                // удалить все
    void swap(List &t) noexcept;        // обменять с заданным списком

private:
    Node *data_;
    Node *head_ = nullptr;
    Node *tail_ = nullptr;

    size_t size_;
    iterator it;
};

#endif //LAB_4_LIST_H
