#pragma once
#include <iostream>
#include <iterator>
#include <utility>
#include <memory>
#include <memory_resource>
#include <algorithm>
#include <cassert>
#include <cstddef>

/*
*    Управление динамической памятью:
*        – перегрузить операции new/delete для класса List;
*        – использовать стандартный аллокатор (распределитель памяти);
*/

//template <typename T, typename Alloc = std::allocator<T> >
//class List
//{
//private:
//    struct Node
//    {
//        Node *current_ = nullptr;
//        Node *next_ = nullptr;
//        T data_;
//    }; // end of Node struct
//
//public:
//    // Usings
//    using value_type = T;
//    using allocator_type = Alloc;
//    using Alloc_Traits = std::allocator_traits<Alloc>;
//    using Node_Alloc_Traits = typename Alloc_Traits::template rebind_traits<Node>;
//
//    static_assert((std::is_same<value_type, typename allocator_type::value_type>::value), "Invalid allocator::value_type");
//
//    using reference = typename allocator_type::reference;
//    using const_reference =  typename allocator_type::const_reference;
//    using pointer = typename allocator_type::pointer;
//    using const_pointer =  typename allocator_type::const_pointer;
//
//    using size_type = size_t;
//    using difference_type = ptrdiff_t;
//
//    class Const_Iterator
//    {
//    private:
//        friend class List;
//        explicit Const_Iterator(const Node *ptr) noexcept;
//
//    public:
//        using difference_type = List::difference_type;
//        using value_type = List::value_type;
//        using pointer = List::const_pointer;
//        using reference = List::const_reference;
//        using iterator_category = std::bidirectional_iterator_tag;
//
//        Const_Iterator() : current_(nullptr) {};
//        reference operator*() const noexcept;
//        Const_Iterator &operator++() noexcept;
//        Const_Iterator &operator--() noexcept;
//        Const_Iterator operator++(int) noexcept;
//        Const_Iterator operator--(int) noexcept;
//        bool operator==(Const_Iterator rhs) const noexcept;
//        bool operator!=(Const_Iterator rhs) const noexcept;
//
//    protected:
//        const Node *Get() const noexcept;
//
//        const Node *current_;
//    };  // end of Const_Iterator class
//
//    class Iterator : public Const_Iterator
//    {
//    private:
//        friend class List;
//
//    public:
//        using difference_type = List::difference_type;
//        using value_type = List::value_type;
//        using pointer = List::pointer;
//        using reference = List::reference;
//        using iterator_category = std::bidirectional_iterator_tag;
//
//        Iterator() noexcept : Const_Iterator() {};
//        explicit Iterator(Node *ptr) noexcept;
//        reference operator*() const noexcept;
//        Iterator &operator++() noexcept;
//        Iterator &operator--() noexcept;
//        Iterator operator++(int) noexcept;
//        Iterator operator--(int) noexcept;
//    };  // end of Iterator class
//
//    using iterator = Iterator;
//    using const_iterator = Const_Iterator;
//
//    explicit List(const allocator_type& alloc = Alloc() );
//    List(const std::initializer_list<value_type> &items, const T &value = T(), const Alloc &alloc = Alloc() );
//    List(const List &other) noexcept;          // copy ctor
//    List(List &&other) noexcept;              // move ctor
//    List &operator=(const List &other);     // copy assign
//    List& operator=(std::initializer_list<value_type>);
//    ~List();
//
//    allocator_type get_allocator() const noexcept;
//
//    const_iterator begin() const noexcept;
//    const_iterator end() const noexcept;
//    iterator begin() noexcept;
//    iterator end() noexcept;
//
//    reference front();
//    reference back();
//
//    bool is_element_exsist(const value_type &item); // ?? TO -> delete
//    bool is_empty() const noexcept;
//    size_type size() const noexcept;
//
//    iterator find(value_type &item) noexcept;
//    const_iterator find(const value_type &item) const noexcept;
//
//    void push_front(const value_type &rhs);
//    void push_front(value_type &&tmp);
//    void push_back(const T &obj);
//    void push_back(T &&tmp);
//
//    iterator insert(const size_type index, const value_type &value);
//    iterator insert(const_iterator index, value_type&& value);
//
//    iterator erase(const_iterator position);
//    iterator erase(const_iterator position, const_iterator last);
//    void clear() noexcept;
//
//    void pop_front() noexcept;
//    void pop_back() noexcept;
//
//    void swap(List &t)  noexcept(std::allocator_traits<allocator_type>::is_always_equal::value);
//
//
//private:
//    void copy(const List &obj);
//
//    Node *head_;
//    Node *tail_;
//    size_type size_;
//    Node_Alloc_Traits  alloc_;
//};
//--------------------------------------------------------------------------------
// class List by new implementation
//--------------------------------------------------------------------------------
namespace dlist_details
{
    template <typename Tp> struct node;

    template <typename Tp> struct node_base
    {
        node<Tp> *prev_;
        node<Tp> *next_;

        node_base() : prev_(nullptr), next_(nullptr) {}
        node_base(node_base &&rhs) : prev_(rhs.prev_), next_(rhs.next_) { rhs.next_, rhs.prev_ = nullptr; }
        node_base &operator=(node_base &&rhs)
        {
            if (&rhs != this)
            {
                prev_ = rhs.prev_;
                next_ = rhs.next_;
                rhs.prev_, rhs.next_ = nullptr;
            }
            return *this;
        }
        node_base(const node_base &) = delete;
        node_base &operator=(const node_base &) = delete;
    };

    template <typename Tp> struct node : node_base<Tp>
    {
        union { Tp value_; };
    };

    template <typename Tp> struct const_iterator
    { // TODO подумать нужен ли метод Get ??
        using value_type = Tp;
        using pointer = Tp const *;
        using reference = Tp const &;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        reference operator*() const { return current_->next_->value_; }
        pointer operator->() const { return std::addressof(current_->next_->value_); }

        const_iterator &operator++()
        {
            current_ = current_->next_;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        const_iterator &operator--() noexcept
        {
            current_ = current_->prev_;
            return current_;
        }

        const_iterator &operator--(int) noexcept
        {
            const_iterator tmp(*this);
            --*this;
            return tmp;
        }

        bool operator==(const_iterator other) const { return current_ == other.current_; }
        bool operator!=(const_iterator other) const { return !operator==(other); }

        node_base<Tp> *current_;
//        const Node *Get() const noexcept;


        explicit const_iterator(const node_base<Tp> *prev) : current_(const_cast<node_base<Tp> *>(prev)) {}
    };

    template <typename Tp> struct iterator : public const_iterator<Tp>
    {
        using Base = const_iterator<Tp>;

        using pointer = Tp *;
        using reference = Tp &;

        reference operator*() const { return this->current_->next_->value_; }
        pointer operator->() const { return std::addressof(this->current_->next_->value_); }

        iterator &operator++()
        {
            Base::operator++();
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++*this;
            return tmp;
        }

        iterator() : const_iterator<Tp>(nullptr) {}
        explicit iterator(node_base<Tp> *prev) : const_iterator<Tp>(prev) {}
    };
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc = std::allocator<T> >
class List
{
public:
    // Usings

    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using difference_type = std::ptrdiff_t;
    using size_type = size_t;
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    using iterator = dlist_details::iterator<T>;
    using const_iterator = dlist_details::const_iterator<T>;
    using traits = std::allocator_traits<allocator_type>;

//    using Node_Alloc_Traits = typename Alloc_Traits::template rebind_traits<Node>;

    List(allocator_type a = {} ) : head_(nullptr), ptail(&head_), size_(0), alloc_(a) {}
    List(const List &other, allocator_type a = {} );
    List(List &&other) noexcept;
    List(List &&other, allocator_type a);

    List &operator=(const List &other);
    List &operator=(List &&other);
    void swap(List &other) noexcept;


private:
    using node_base = dlist_details::node_base<T>;
    using node = dlist_details::node<T>;

    node_base head_;
    node_base *ptail_;
    size_type size_;
    allocator_type  alloc_;
};
//--------------------------------------------------------------------------------
template <typename T>
class Allocator
{
public:
    using value_type = T;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;


    Allocator() noexcept;
    Allocator(const Allocator &a) noexcept;
    template<class U> Allocator(const Allocator<U> &a) noexcept;
    ~Allocator();

    void* allocate(size_t n)
    {
        return ::operator new(n * sizeof(T) );
    }

    void deallocate(T *ptr, size_t)
    {
        ::operator delete(ptr);
    }

    template <typename... Args>
    void construct(T *ptr, const Args&... args)
    {
        new(ptr) T(args...);
    }

    void destroy(T *ptr) noexcept
    {
        ptr->~T();
    }
};

template <typename T, typename U>
bool operator ==(Allocator<T> const &a_t, Allocator<U> const &a_u) noexcept;

template <typename T, typename U>
bool operator !=(Allocator<T> const &a_t, Allocator<U> const &a_u) noexcept;
//--------------------------------------------------------------------------------