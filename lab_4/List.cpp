#include "List.h"

// class Node
//----------------------------------------------------------------------
List::Node::Node(Record item) noexcept
: prev_(nullptr), next_(nullptr), data_{ std::move(item) }
{}
//----------------------------------------------------------------------
bool List::Node::operator==(const_reference item) const noexcept
{
    return data_ == item.data_;
}
//----------------------------------------------------------------------




// class Const_Iterator
//----------------------------------------------------------------------
List::Const_Iterator::Const_Iterator(const value_type *ptr) noexcept
: current_(ptr)
{}
//----------------------------------------------------------------------
List::Const_Iterator::reference List::Const_Iterator::operator*() const noexcept
{
    return current_->data_;
}
//----------------------------------------------------------------------
List::Const_Iterator &List::Const_Iterator::operator++() noexcept
{
    current_ = current_->next_;
    return *this;
}
//----------------------------------------------------------------------
List::Const_Iterator &List::Const_Iterator::operator--() noexcept
{
    current_ = current_->prev_;
    return *this;
}
//----------------------------------------------------------------------
List::Const_Iterator List::Const_Iterator::operator++(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->next_;
    return copy;
}
//----------------------------------------------------------------------
List::Const_Iterator List::Const_Iterator::operator--(int) noexcept
{
    List::Const_Iterator copy = *this;
    current_ = current_->prev_;
    return copy;
}
//----------------------------------------------------------------------
bool List::Const_Iterator::operator==(Const_Iterator rhs) const noexcept
{
    return current_ == rhs.current_;
}
//----------------------------------------------------------------------
bool List::Const_Iterator::operator!=(Const_Iterator rhs) const noexcept
{
    return !(*this == rhs);
}
//----------------------------------------------------------------------
const List::Node *List::Const_Iterator::Get() const noexcept
{
    return current_;
}
//----------------------------------------------------------------------




// class Iterator
//----------------------------------------------------------------------
List::Iterator::Iterator(value_type *ptr) noexcept
: Const_Iterator(ptr)
{}
//----------------------------------------------------------------------
List::reference List::Iterator::operator*() const noexcept
{
    auto &&res = Const_Iterator::operator*();
    return const_cast<reference>(res);
}
//----------------------------------------------------------------------
List::Iterator &List::Iterator::operator++() noexcept
{
    Const_Iterator::operator++();
    return *this;
}
//----------------------------------------------------------------------
List::Iterator &List::Iterator::operator--() noexcept
{
    Const_Iterator::operator--();
    return *this;
}
//----------------------------------------------------------------------
List::Iterator List::Iterator::operator++(int) noexcept
{
    auto res = Const_Iterator::operator++(0);
    return List::Iterator {const_cast<pointer>(res.Get() ) };
}
//----------------------------------------------------------------------
List::Iterator List::Iterator::operator--(int) noexcept
{
    auto res = Const_Iterator::operator--(0);
    return Iterator {const_cast<pointer>(res.Get() ) };
}
//----------------------------------------------------------------------




// class List
//----------------------------------------------------------------------
List::List(int size)
: size_(size), head_(nullptr), tail_(nullptr)
{}
//----------------------------------------------------------------------
List::List(const std::initializer_list<value_type> &items)
: List()
{
    for (auto &item : items)
        push_back(item);
}
//----------------------------------------------------------------------
List::List(const List &other) noexcept // copy ctor
: List(0)
{
    copy(other);
}
//----------------------------------------------------------------------
List::List(List &&other) noexcept // move ctor
: size_(other.size_), head_(std::move(other.head_) ), tail_(std::move(other.tail_) )
{}
//----------------------------------------------------------------------
List &List::operator=(const List &other) // copy assign
{
    if (this != &other)
    {
        size_ = other.size_;
        copy(other);
    }
    return *this;
}
//----------------------------------------------------------------------
List &List::operator=(List &&other) noexcept // move assign
{
    if (this != &other)
    {
        size_ = other.size_;
        head_ = std::move(other.head_);
        tail_ = std::move(other.tail_);
    }
    return *this;
}
//----------------------------------------------------------------------
List::~List()
{
    clear();
}
//----------------------------------------------------------------------
List::const_iterator List::begin() const noexcept
{
    return const_iterator(head_);
}
//----------------------------------------------------------------------
List::const_iterator List::end() const noexcept
{
    return const_iterator(nullptr);
}
List::const_iterator List::cbegin() const noexcept
{
    return const_iterator(head_);
}
//----------------------------------------------------------------------
List::const_iterator List::cend() const noexcept
{
    return const_iterator(nullptr);
}
//----------------------------------------------------------------------
List::iterator List::begin() noexcept
{
    return iterator(head_);
}
//----------------------------------------------------------------------
List::iterator List::end() noexcept
{
    return iterator(nullptr);
}
//----------------------------------------------------------------------
List::reference List::front()
{
    return *head_;
}
//----------------------------------------------------------------------
List::reference List::back()
{
    return *tail_;
}
//----------------------------------------------------------------------
bool List::empty() const noexcept
{
    return size_ == 0;
}
//----------------------------------------------------------------------
List::size_type List::size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------
void List::push_front(const_reference rhs)
{ // добавить в начало; Time Complexity: O(1)
    auto new_node = new Node(rhs);
    if (head_)
    {
        head_->prev_ = new_node;
        new_node->next_ = head_;
        head_ = new_node;
    }
    else
        head_ = tail_ = new_node;

    ++size_;
}
//----------------------------------------------------------------------
void List::push_front(value_type &&tmp)
{ // добавить в начало - временный объект --
    auto new_node = new Node(std::move(tmp) ); // создаю новую Node и перемещаю данные rvalue
    if (head_)
    {
        head_->prev_ = new_node;
        new_node->next_ = head_;
        head_ = new_node;
    }
    else
        head_ = tail_ = new_node;

    ++size_;
}
//----------------------------------------------------------------------
void List::pop_front() noexcept
{
    erase(begin() );
}
//----------------------------------------------------------------------
void List::push_back(const_reference obj)
{ // добавить в конец
    auto new_node = new Node(obj); // создан новый объект Node<T> в куче

   if (tail_)
   {
       tail_->next_ = new_node;
       new_node->prev_ = tail_;
       tail_ = new_node;
   }
   else
       head_ = tail_ = new_node;

    ++size_;
}
//----------------------------------------------------------------------
void List::push_back(value_type &&tmp)
{ // добавить в начало - временный объект --
    auto new_node = new Node(std::move(tmp) );
    if (tail_)
    {
        tail_->next_ = new_node;
        new_node->prev_ = tail_;
        tail_ = new_node;
    }
    else // список пуст
        head_ = tail_ = new_node;

    ++size_;
}
//----------------------------------------------------------------------
void List::pop_back() noexcept
{ // удалить последний
    if ( tail_ == head_) // список пуст
        return;

    tail_->prev_ = nullptr;
    tail_ = tail_->prev_;

    --size_;
}
//----------------------------------------------------------------------
void List::insert(const_iterator fnd, const_reference obj)
{ // вставить в позицию итератора
    auto ptr = const_cast<pointer>(fnd.Get() ); // Node *
    if (!ptr) // вставка в конец
    {
        push_back(obj);
        return;
    }

    auto new_node = new value_type (obj);
    new_node->next_ = ptr; // т.к. вставляем до итератора
    new_node->prev_ = ptr->prev_;

    if (ptr->prev_) // вставка в голову списка
        ptr->prev_->next_ = new_node;

    ptr->prev_ = new_node;

    ++size_;
}
//----------------------------------------------------------------------
void List::insert(iterator fnd, value_type &&tmp)
{  // вставить временный объект --
    auto ptr = const_cast<pointer>(fnd.Get() ); // снятие константности и разыменование указателя

    if (!ptr)
    {
        push_back(std::move(tmp) );
        return;
    }

    auto new_node = new value_type (std::move(tmp) );
    new_node->next_ = ptr;
    new_node->prev_ = ptr->prev_;

    if (ptr->prev_)
        ptr->prev_->next_ = new_node;

    ptr->prev_ = new_node;
    ++size_;
}
//----------------------------------------------------------------------
void List::erase(const_iterator place) noexcept
{ // удалить указанный (в позиции) элемент
    auto ptr = const_cast<pointer>(place.Get());

    if (ptr->prev_) // не голова списка
        ptr->prev_->next_ = ptr->next_;
    else
        head_ = ptr->next_;

    if (ptr->next_) // не хвост списка
        ptr->next_->prev_ = ptr->prev_;
    else
        tail_ = ptr->prev_;

    delete ptr;
    --size_;
}
//----------------------------------------------------------------------
void List::clear() noexcept
{ // пройти по всей цепочке и удалить каждую Node
    while (head_)
        delete std::exchange(head_, head_->next_);
    head_ = tail_ = nullptr;
    size_ = 0;
}
//----------------------------------------------------------------------
void List::clear(const_iterator it) noexcept
{
    auto ptr = const_cast<pointer>(it.Get() );
    while (ptr) // не хвост списка
        delete std::exchange(ptr, ptr->next_);
}
//----------------------------------------------------------------------
void List::swap(List &t) noexcept
{ // обменять с заданным списком
    std::swap(size_, t.size_);
    std::swap(head_, t.head_);
    std::swap(tail_, t.tail_);
}
//----------------------------------------------------------------------
void List::copy(const List &obj)
{
    Node *new_obj = obj.head_;
    iterator it = begin();

    // если A < B копировать до A.size(); создать новые элементы в А после позиции A.size()
    if (size() < obj.size() )
    {
        while (it != end())
        {
            *it = new_obj->data_;
            new_obj = new_obj->next_;
            ++it;
        }
        while (new_obj != nullptr)
        {
            push_back(new_obj->data_);
            new_obj = new_obj->next_;
        }
    }
    else
    {
        while (new_obj != nullptr)
        {
            *it = new_obj->data_;
            new_obj = new_obj->next_;
            ++it;
        }

        if (size() > obj.size() )
        {
            tail_ = &(*it);
            clear(it); // удаляем элементы с новой позиции хвоста А
        }
    }
}
//----------------------------------------------------------------------
List::const_iterator List::find(const Node &item) const noexcept
{
    for (auto it = begin(); it != end(); ++it)
        if (*it == item)
            return it;

    return const_iterator {nullptr};
}
//----------------------------------------------------------------------
List::iterator List::find(const_reference item) noexcept
{
    auto it = static_cast<const List &>(*this).find(item);
    return iterator { const_cast<pointer>(it.Get() ) };
}
//----------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, List &list)
{
    int i = 0;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        os << "#" << ++i << '\n';
        os << "Catalog ID: " << (*it).data_.Get_cypher() << "\n";
        os << "Year of publishing: " << (*it).data_.Get_year_of_pub() << "\n";
        os << "Publisher: " << (*it).data_.Get_publisher() << "\n";
        os << "Price: " << (*it).data_.Get_price_() << "\n\n";
    }

    return os;
}
//----------------------------------------------------------------------
#if slow_sort
void Split(List::Node *head, List::Node **a, List::Node **b)
{ // Функция для разделения узлов заданного двусвязного списка на две половины, используя стратегию быстрого/медленного указателя
    List::Node *slow = head;
    List::Node *fast = head->next_;

    // продвигаемся вперед `fast` на два узла и продвигаемся `slow` на один узел
    while (fast != nullptr)
    {
        fast = fast->next_;
        if (fast != nullptr)
        {
            slow = slow->next_;
            fast = fast->next_;
        }
    }

    *b = slow->next_;
    slow->next_ = nullptr;
}
//--------------------------------------------------------------------------------
List::Node *Merge(List::Node *a, List::Node *b)
{ // Рекурсивная функция для объединения узлов двух отсортированных списков в единый отсортированный список

    // базовые случаи
    if (a == nullptr) {
        return b;
    }

    if (b == nullptr) {
        return a;
    }

    // выбираем `a` или `b` и повторяем
    if (a->data_.Get_cypher() <= b->data_.Get_cypher() )
    {
        a->next_ = Merge(a->next_, b);
        a->next_->prev_ = a;
        a->prev_ = nullptr;
        return a;
    }
    else {
        b->next_ = Merge(a, b->next_);
        b->next_->prev_ = b;
        b->prev_ = nullptr;
        return b;
    }
}
//--------------------------------------------------------------------------------
void Merge_Sort(List::Node **head)
{ // Функция для сортировки двусвязного списка с использованием алгоритма сортировки слиянием

    // базовый вариант: 0 или 1 узел
    if (*head == nullptr || (*head)->next_ == nullptr) {
        return;
    }

    // разделить заголовок на подсписки `a` и `b`
    List::Node* a = *head, *b = nullptr;
    Split(*head, &a, &b);

    // рекурсивно сортируем подсписки
    Merge_Sort(&a);
    Merge_Sort(&b);

    // объединяем два отсортированных списка
    *head = Merge(a, b);
}
#endif

void Split(List::Node *head, List::Node **a, List::Node **b)
{ // Функция для разделения узлов заданного двусвязного списка на две половины, используя стратегию быстрого/медленного указателя
    List::Node *slow = head;
    List::Node *fast = head->next_;

    // продвигаемся вперед `fast` на два узла и продвигаемся `slow` на один узел
    while (fast != nullptr)
    {
        fast = fast->next_;
        if (fast != nullptr)
        {
            slow = slow->next_;
            fast = fast->next_;
        }
    }

    *b = slow->next_;
    slow->next_ = nullptr;
}
//--------------------------------------------------------------------------------
List::Node *Merge(List::Node *a, List::Node *b)
{ // Рекурсивная функция для объединения узлов двух отсортированных списков в единый отсортированный список

    // базовые случаи
    if (a == nullptr) {
        return b;
    }

    if (b == nullptr) {
        return a;
    }

    // выбираем `a` или `b` и повторяем
    if (a->data_.Get_cypher() <= b->data_.Get_cypher() )
    {
        a->next_ = Merge(a->next_, b);
        a->next_->prev_ = a;
        a->prev_ = nullptr;
        return a;
    }
    else {
        b->next_ = Merge(a, b->next_);
        b->next_->prev_ = b;
        b->prev_ = nullptr;
        return b;
    }
}
//--------------------------------------------------------------------------------
void Merge_Sort(List::Node **head)
{ // Функция для сортировки двусвязного списка с использованием алгоритма сортировки слиянием

    // базовый вариант: 0 или 1 узел
    if (*head == nullptr || (*head)->next_ == nullptr)
    {
        return;
    }

    // разделить заголовок на подсписки `a` и `b`
    List::Node *a = *head, *b = nullptr;
    Split(*head, &a, &b);

    // рекурсивно сортируем подсписки
    Merge_Sort(&a);
    Merge_Sort(&b);

    // объединяем два отсортированных списка
    *head = Merge(a, b);
}
//--------------------------------------------------------------------------------
void List::Shuffle_Elements()
{
//    Node *current, *next;
//    bool flag = true;
//
//    current = head_;
//    next = head_->next_;
//
//    while (current != nullptr or next != nullptr)
//    {
//        std::swap(current->data_, next->data_);
//
//        current = current->next_->next_;
//        next = next->next_->next_;
//    }

    // Function to swap the k'th node from the beginning with the
    // k'th node from the end in a linked list

    Record k = Record { std::make_tuple(2020, "Berkly", 2.39) };

    bool flag_int, flag_str, flag_double;
    flag_int = flag_str = flag_double = false;

    Node *x, *y, *prev_x = nullptr, *prev_y = head_;

    // Find the k'th node from the beginning and store it in `x`.
    // Also, calculate the previous node of `x` and store it in `prev_x`.
    Node *curr = head_;

    for (auto it = begin(); it != end(); it++)
    {
        if ((*it).data_.Get_year_of_pub() == k.Get_year_of_pub() )
            flag_int = true;
        if ((*it).data_.Get_publisher() == k.Get_publisher() )
            flag_str = true;
        if ((*it).data_.Get_price_() == k.Get_price_() )
            flag_double = true;



        if (flag_int == true and flag_str == true and flag_double == true)
            break;

        prev_x = curr;
        curr = curr->next_;
    }

    x = curr;

    // If `k` is more than the total number of nodes, X and Y doesn't exist
    if (curr == nullptr)
        return;

    // Find the k'th node from the end and store it in `y`.
    // Also, calculate the previous node of `y` and store it in `prev_y`.
    Node *ptr = head_;
    while (curr->next_)
    {
        prev_y = ptr;
        ptr = ptr->next_;
        curr = curr->next_;
    }
    y = ptr;


    if (x->next_ == y)
    { // Y is next to X (X —> Y)
        x->next_ = y->next_;
        y->next_ = x;

        if (prev_x != nullptr && prev_x != x)
            prev_x->next_ = y;
        else
            head_ = y;
    }
    else if (y->next_ == x)
    { // X is next to Y (Y —> X)
        y->next_ = x->next_;
        x->next_ = y;

        if (prev_y != nullptr && prev_y != y)
            prev_y->next_ = x;
        else
            head_ = x;
    }
    else if (x == head_)
    { // X is the head node
        head_ = y;
        y->next_ = x->next_;
        prev_y->next_ = x;
        x->next_ = nullptr;
    }
    else if (y == head_)
    { // Y is the head node
        head_ = x;
        x->next_ = y->next_;
        prev_x->next_ = y;
        y->next_ = nullptr;
    }
    else
    { // Otherwise
        ptr = y->next_;
        y->next_ = x->next_;
        x->next_ = ptr;

        prev_x->next_ = y;
        prev_y->next_ = x;
    }
}
//--------------------------------------------------------------------------------