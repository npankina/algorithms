/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */
#pragma once
#include <iostream>
#include <iterator>
#include <utility>
#include <memory>
#include <algorithm>
#include <cassert>

/*
*    Управление динамической памятью:
*        – перегрузить операции new/delete для класса List;
*        – использовать стандартный аллокатор (распределитель памяти);
*/
//--------------------------------------------------------------------------------
namespace dlist_details
{
    template <typename T>
    struct Node
    {
        Node() : prev_(nullptr), next_(nullptr) {};
        Node(Node &&rhs) : prev_(rhs.prev_), next_(rhs.next_), data_{std::move(rhs.data_)}
        {
            rhs.next_, rhs.prev_ = nullptr;
        }
        Node &operator=(Node &&rhs)
        {
            if (&rhs != this)
            {
                prev_ = rhs.prev_;
                next_ = rhs.next_;
                data_ = std::move(rhs.data_);
                rhs.prev_, rhs.next_ = nullptr;
            }
        }

        Node(const Node &) = delete;
        Node &operator=(const Node &) = delete;

        Node *prev_;
        Node *next_;
        T data_;
    }; // end of Node struct
//--------------------------------------------------------------------------------
    template <typename T>
    class Const_Iterator
    {
    private:
        friend class List;
        explicit Const_Iterator(const Node<T> *ptr) noexcept;

    public:
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        Const_Iterator() : current_(nullptr) {};
        reference operator*() const { return *current_; } // return current_->next_->value_;
        Const_Iterator &operator++() noexcept
        {
            current_ = current_->next_;
            return *this;
        }
        Const_Iterator &operator--() noexcept { current_ = current_->prev_; }
        Const_Iterator operator++(int) noexcept
        {
            Const_Iterator copy(*this);
            current_ = current_->next_;
            return copy;
        }
        Const_Iterator operator--(int) noexcept
        {
            Const_Iterator copy(*this);
            current_ = current_->prev_;
            return copy;
        }
        bool operator==(Const_Iterator rhs) const noexcept { return current_ == rhs.current_; }
        bool operator!=(Const_Iterator rhs) const noexcept { return !operator==(rhs); } // !(*this == rhs)

    protected:
        const Node<T> *Get() const noexcept;

        const Node<T> *current_;
    };  // end of Const_Iterator class
//--------------------------------------------------------------------------------
    template <typename T>
    class Iterator : public Const_Iterator<T>
    {
    private:
        friend class List;

    public:
        using Base = Const_Iterator<T>;
        using pointer = T *;
        using reference = T &;


        Iterator() noexcept : Const_Iterator<T>(nullptr) {};
        explicit Iterator(Node<T> *ptr) : Const_Iterator<T>(ptr) {}
        reference operator*() const noexcept
        {
            auto &&res = std::move(Base::operator*());
            return const_cast<reference>(res);
        }
        Iterator &operator++() noexcept
        {
            Base::operator++();
            return *this;
        }
        Iterator &operator--() noexcept
        {
            Base::operator--();
            return *this;
        }
        Iterator operator++(int) noexcept
        {
//            Iterator res(*this);
//            ++*this;
//            return  res;
             auto res = Base::operator++(0);
             return Iterator {const_cast<pointer>(res.Get() ) };
        }
        Iterator operator--(int) noexcept
        {
             auto res = Base::operator--(0);
             return Iterator {const_cast<pointer>(res.Get() ) };
        }
    };  // end of Iterator class
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc = std::allocator<T> >
class List
{
public:
    using value_type = T;
    using allocator_type = Alloc;
    using Alloc_Traits = std::allocator_traits<allocator_type>;
    using Node_Alloc_Traits = typename Alloc_Traits::template rebind_traits<dlist_details::Node<T> >;
    using reference = value_type &;
    using const_reference =  const value_type &;
    using pointer = value_type *;
    using const_pointer =  const value_type *;
    using iterator = dlist_details::Iterator<T>;
    using const_iterator = dlist_details::Const_Iterator<T>;
    using size_type = size_t;

    explicit List(const allocator_type &a = Alloc() ) : head_(nullptr), tail_(nullptr), size_(0), alloc_(a) {}
    List(const std::initializer_list<value_type> &rhs, const Alloc &a = Alloc() );
    List(const List &other, allocator_type a = {} ) noexcept;          // copy ctor
    List(List &&other) noexcept;              // move ctor
    List(List &&other, allocator_type a);
    ~List();

    List &operator=(const List &other);     // copy assign
    List &operator=(List &&other);          // move assign
    void swap(List &other)  noexcept(std::allocator_traits<allocator_type>::is_always_equal::value);

    size_type size() const noexcept { return size_; }
    bool is_empty() const noexcept { return 0 == size_; }

    const_iterator cbegin() const { return const_iterator(head_) ; }
    const_iterator cend() const { return const_iterator(tail_); }
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(tail_); }

    reference front() { return head_->next_->data_; }
    const_reference front() const { return head_->next_->data_; }

    template <typename... Args> iterator emplace(iterator it, Args &&... args);
    template<typename... Args> void emplace_front(Args &&... args) { emplace(begin(), forward<Args>(args)...); }

    iterator find(const value_type &item);

    iterator insert(iterator i, const T &v) { return emplace(i, v); }
    void push_front(const value_type &v) { emplace(begin(), v); }
    void push_back(const T &v) { emplace(end(), v); }

    /* Note: erasing elements invalidates iterators to the node
     following the element being erased. */
    iterator erase(iterator b, iterator e);
    iterator erase(iterator it)
    {
        iterator end = it;
        return erase(it, ++end);
    }

    void pop_front() { erase(begin()); }
    void pop_back() { erase(end()); } // TODO Check is iterator invalidates??
    allocator_type get_allocator() const { return alloc_; }


private:
    using node = dlist_details::Node<T>;

    node *head_;
    node *tail_;
    size_type size_;
    Node_Alloc_Traits  alloc_;
};
//--------------------------------------------------------------------------------
namespace
{
    template <typename T>
    bool operator==(List<T> &a, const List<T> &b)
    {
        if (a.size() != b.size())
            return false;
        return std::equal(a.begin(), a.end(), b.begin());
    }
}
//--------------------------------------------------------------------------------



// Implementation
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List(const std::initializer_list<value_type> &rhs, const Alloc &a)
: List<T, Alloc>(a)
{
    // TODO
    for (const value_type &v: rhs)
        push_back(v);
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List(const List &other, allocator_type a) noexcept         // copy ctor
: List<T, Alloc>(a)
{
    operator=(other);
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List(List &&other) noexcept // move ctor
: List<T, Alloc>(other.get_allocator())
{
    head_ = std::move(other.head_);
    tail_ = std::move(other.tail_);
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List(List &&other, allocator_type a)
: List<T, Alloc>(a)
{
    operator=(std::move(other));
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::~List()
{
    erase(begin(), end());
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc> &List<T, Alloc>::operator=(const List &other)    // copy assign
{
    if (&other != this)
    {
        erase(begin(), end());
        for (const value_type &v: other)
            push_back(v);
    }
    return *this;
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc> &List<T, Alloc>::operator=(List &&other)         // move assign
{
    if (&other != this)
    {
        if (alloc_ == other.alloc_)
        {
            erase(begin(), end());
            swap(other);
        }
        else
            operator=(other); // copy assign
    }
    return *this;
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::swap(List &other)  noexcept(std::allocator_traits<allocator_type>::is_always_equal::value)
{
    assert(alloc_ == other.alloc_);
    node *new_tail = other.is_empty() ? head_ : other.tail_;
    node *new_other_tail = is_empty() ? other.head_ : tail_;
    std::swap(head_->next_, other.head_->next_);
    std::swap(size_, other.size_);
    tail_ = new_tail;
    other.tail_ = new_other_tail;
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
template <typename... Args>
typename List<T, Alloc>::iterator List<T, Alloc>::emplace(List<T, Alloc>::iterator it, Args &&...args)
{
//    node *new_node = static_cast<node *>(alloc_.allocate(sizeof(node)));
    node *new_node = alloc_.allocate(sizeof(node)); // TODO ???

    try {
        alloc_.construct(std::addressof(new_node->value_), std::forward<Args>(args)...);
    } catch (...)
    { // Recover resources if exception on constructor call.
//        alloc_.resource()->deallocate(new_node, sizeof(node), alignof(node));
        alloc_.deallocate(new_node, sizeof(node));
        throw;
    }

    new_node->next_ = it.current_->next_;
    it.current_->next_ = new_node;
    if (it.current_ == tail_)
        tail_ = new_node; // Added at end
    ++size_;
    return it;
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::find(const value_type &item)
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::erase(iterator b, iterator e)
{
    node *erase_next = b.current_->next_;
    node *erase_past = e.current_->next_;

    if (nullptr == erase_past)
        tail_ = b.current_;
    b.current_->next_ = erase_past;
    while (erase_next != erase_past)
    {
        node *old_node = erase_next;
        erase_next = erase_next->next_;
        --size_;
        (old_node->value_)->~T();
        alloc_.destroy(old_node->value_);
//        alloc_.resource()->deallocate(old_node, sizeof(node), alignof(node));
    }
    return b;
}
//--------------------------------------------------------------------------------