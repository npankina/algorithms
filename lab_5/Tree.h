#ifndef LAB_5_TREE_H
#define LAB_5_TREE_H

#include <tuple>

class Tree
{
public:
    using key_t   = uint64_t;
    using value_t = std::tuple</* something */>;
    using data_t  = std::tuple<key_t, value_t>;

private:
    struct node_t
    {
        struct node_t *parent_;
        struct node_t *left_;
        struct node_t *right_;
        void *data_; // TODO T? какой тип данных будет в data_
    };

public:
    Tree(void);
    virtual ~Tree(void);
    Tree(const data_t &d);
    Tree(const std::initializer_list<data_t> &t);
    Tree(const Tree &other);
    Tree(Tree &&other) noexcept;                // -- конструктор переноса --
    Tree &operator=(Tree &&other) noexcept;     // -- операция перемещания --
    Tree &operator=(const Tree &other);
    // Количества ------------------
    bool empty() const noexcept;
    size_t count() const noexcept;              // -- количенство элементов --
    size_t height() const noexcept;             // -- высота дерева --
    // Поиск -----------------------
    data_t find(const key_t &key) const;
    // Модификаторы контейнера --
    // Вставить --
    bool insert(const key_t &key, const value_t &v);
    bool insert(const data_t &d);
    // Заменить --
    bool replace(const key_t &key, const value_t &v);
    // Удалить --
    bool erase(const key_t &key);              // удалить указанный
    void clear();                              // удалить все
    // обмен --
    void swap(Tree &t) noexcept;        // обменять с заданным списком
};

#endif //LAB_5_TREE_H