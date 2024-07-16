#pragma once
#include <utility>

template <typename T>
class Node
{
public:
    Node(T item, Node *left = nullptr, Node *right = nullptr) : data_(item), left_(left), right_(right) {};

    T data_;
    Node *left_;
    Node *right_;
    // Node *parent_;
};

template <typename T>
class Tree
{
public:

    ~Tree();
    Tree();

    void Insert(T elem);
    void Delete(T &elem);
    T Find(const T &elem);

    size_t Size() { return size_; }

private:
    Node<T> *root_;
    size_t size_;
};

/* Бинарное дерево
 * первое число переданное в структуры данных - становится его корнем.
 * когда потомков нет, указатели на левого и правого потомка указывают на nullptr
 * в левую часть пойдет число < корень, в правую >= корень
 * Бинарное дерево - всегда отсортировано
 */