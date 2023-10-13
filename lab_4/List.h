#ifndef LAB_4_LIST_H
#define LAB_4_LIST_H

#include <iostream>
#include <tuple>
#include <iterator>
#include <vector>
#include <string>
//--------------------------------------------------------------------------------
namespace tool
{
    static const int lib_arr_size = 20;
    static int cypher = 10000006;
    static int subscribers_cypher = 10000;
}
//--------------------------------------------------------------------------------
class Record
{
public:
    Record(int cypher = tool::cypher++, int year=2023, std::string pub = "Berkly", double price = 10.);
    Record(const Record &lvalue); // copy ctor
    Record(Record &&rvalue); // move ctor
    Record &operator=(const Record &lvalue); // copy assign
    Record &operator=(Record &&rvalue); // move assign

private:
    int cypher_;
    int year_of_pub;
    std::string publisher;
    double price_;
};
//--------------------------------------------------------------------------------
class List
{
private:
    struct Node
    { // вложенный т.к. не имеет смысла без класса контейнера, более того - ни один из методов класса-контейнера не возвращает тип Node
        Record data_;
        Node *prev_, *next_;

        Node();
        Node(const Record &lvalue, Node *prev = nullptr, Node *next = nullptr);  // copy ctor
        Node(Record &&rvalue, Node *prev = nullptr, Node *next = nullptr);  // move ctor
        Node(Node *prev, Node *next);
    };

public:
    // -- типы – определить самостоятельно --
    using size_type = size_t;
    using value_type = Node;
    using reference = value_type &;
    using const_reference = const value_type &;

private:
    // -- структура элемента списка – определить самостоятельно --
    size_type size_;
    value_type *head_, *tail_;

public:
    struct iterator
    { // -- Вложенный класс-итератор –
        Node *ptr_;

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Node;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

        iterator(const iterator &) = default; // copy ctor
        iterator &operator=(const iterator &) = default; // copy assign

        explicit iterator(value_type *t) noexcept;
        iterator() noexcept;

        bool operator==(const iterator &it) const noexcept;
        bool operator!=(const iterator &it) const noexcept;

        // Перемещение итератора
        iterator &operator++() noexcept;
        iterator &operator--() noexcept;
        iterator &operator++(int) noexcept;
        iterator &operator--(int) noexcept;
        reference operator*() const noexcept;
    };  // -- конец итератора --

    /* Конструкторы/деструктор/присваивания */
    List(size_type sz = 0);
    virtual ~List();
    List(const std::initializer_list<value_type> &t);
    List(const List& other) noexcept;
    List(List&& other) noexcept;              // -- конструктор переноса --
    List& operator=(List&& other) noexcept;   // -- операция перемещения --
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
//--------------------------------------------------------------------------------
class Subscriber
{
public:
    explicit Subscriber(std::string name = "", int t_books = 0, int s_cypher = tool::subscribers_cypher++);

//    Subscriber(const Subscriber &lvalue); // copy ctor
//    Subscriber(Subscriber &&rvalue); // move ctor
//    Subscriber &operator=(const Subscriber &lvalue); // copy assign
//    Subscriber &operator=(Subscriber &&rvalue); // move assign

    void add_book();
    void replace_book();
    void delete_book();
    void search_by_book_cypher();
    void search_by_price();

private:
    static const int size = 10;

    List lib_data; // данные о взятых книгах
    std::string last_name;
    int taken_books; // количество полученных книг
    int sub_cypher; // шифр пользователя
};
//--------------------------------------------------------------------------------
namespace data_storage
{
    Record Lib[tool::lib_arr_size] {
            Record(10000001, 2019, "Oxford", 12.0),
            Record(10000002, 2014, "Berkly", 7.50),
            Record(10000003, 2018, "Norman", 2.35),
            Record(10000004, 2017, "Sky", 1.19),
            Record(10000005, 2020, "Sherman", 35.0)
    };
}
//--------------------------------------------------------------------------------
#endif //LAB_4_LIST_H