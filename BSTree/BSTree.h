#pragma once
#include <functional>
#include <iterator>

template <typename T>
class BSTree
{
public :
    using value_type = T;
    using size_type = size_t;

private:
    class Node_
    {
    public:
        Node_() : data_(), left_(nullptr), right_(nullptr) {}
        Node_(const T &data, Node_ *left=nullptr, Node_ *right=nullptr): data_(data), left_(left), right_(right) {}
        Node_(T &&data, Node_ *left=nullptr, Node_ *right=nullptr): data_(std::move(data)), left_(left), right_(right) {}

        Node_ *left_;
        Node_ *right_;
        T data_;
    };

    Node_ *root_;
    size_t size_;
    size_t height_;

public:
    BSTree(void);
    virtual ~BSTree(void);
    BSTree(const T &d);
    BSTree(const std::initializer_list<T> &t);
    BSTree(const BSTree &other);
    BSTree(BSTree &&other) noexcept;
    BSTree& operator=(BSTree &&other) noexcept;
    BSTree& operator=(const BSTree &other);

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t height() const noexcept;
    void in_order();
    const T* find(const T &f) const;
    bool insert(const T &d);
    // bool replace(const Key &key, const T &v);
    bool erase(const T &key);
    void clear();
    void copy();
    void swap(BSTree &t) noexcept;
};