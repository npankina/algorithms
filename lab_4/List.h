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
    Record(std::tuple<int, std::string, double> &&item);
    Record(const Record &lvalue); // copy ctor
    Record(Record &&rvalue); // move ctor
    Record &operator=(const Record &lvalue); // copy assign
    Record &operator=(Record &&rvalue); // move assign

    bool operator==(const Record &item)  const noexcept;

private:
    int cypher_;
    int year_of_pub;
    std::string publisher;
    double price_;
};
//--------------------------------------------------------------------------------
Record Make_Tuple_for_Record(int year, std::string pub, double price)
{
    return Record(std::make_tuple(year, pub, price) );
}
//--------------------------------------------------------------------------------
class List
{
private:
    struct Node;
public:
    using value_type = Node;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = Node *;
    using const_pointer = const Node *;
    using reference = Node &;
    using const_reference = const Node &;

private:
    struct Node
    { // вложенный т.к. не имеет смысла без класса контейнера, более того - ни один из методов класса-контейнера не возвращает тип Node
        Node *prev_ = nullptr;
        Node *next_ = nullptr;
        Record data_;

        Node(Record item) noexcept;
        bool operator==(const_reference item)  const noexcept;
    };

public:
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
    };  // -- конец const-итератора --

    class Iterator : public Const_Iterator
    {
    private:
        friend class List;
        explicit Iterator(Node *ptr) noexcept;

    public:
        using difference_type = List::difference_type;
        using value_type = List::value_type;
        using pointer = List::pointer;
        using reference = List::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        reference operator*() const noexcept;
        Iterator &operator++() noexcept;
        Iterator &operator--() noexcept;
        Iterator operator++(int) noexcept;
        Iterator operator--(int) noexcept;
    };  // -- конец итератора --

    using iterator = Iterator;
    using const_iterator = Const_Iterator;


    /* Конструкторы/деструктор/присваивания */
    List();
    List(const std::initializer_list<value_type> &items);
    List(const List &other) noexcept;          // copy ctor
    List(List &&other) noexcept;              // move ctor
    List &operator=(List && other) noexcept;  // move assign
    List &operator=(const List &other);     // copy assign
    ~List();


    // Итераторы ----------------
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

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
    void pop_front () noexcept;               // удалить первый
    void push_back (const_reference);         // добавить в конец
    void push_back (value_type &&);           // добавить в начало - временный объект --
    void pop_back ();                         // удалить последний
    void insert (Const_Iterator, const_reference);  // вставить в позицию итератора
    const_iterator find(const Node &item) const noexcept;
    iterator find(const_reference item) noexcept;
    Iterator insert (Iterator, value_type&&);     // вставить временный объект --
    Iterator erase (const_iterator place) noexcept;                    // удалить указанный (в позиции)
    void clear () noexcept;                                // удалить все
    void swap (List &t) noexcept;        // обменять с заданным списком

private:
    // -- структура элемента списка – определить самостоятельно --
    size_type size_;
    pointer head_;
    pointer tail_;
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

//--------------------------------------------------------------------------------
#endif //LAB_4_LIST_H