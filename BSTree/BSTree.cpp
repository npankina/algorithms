#include "BSTree.h"


//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(void) noexcept
: root_(nullptr), size_(0), height_(0)
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::~BSTree(void)
{
    clear();
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(const T &d) : BSTree()
{
    insert(d);
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(const std::initializer_list<T> &t)
{
    if (t.empty() )
        return;

    for (auto it = t.begin(), end = t.end(); it != end; ++it)
        insert(*it);
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(const BSTree &other) : BSTree() // copy ctor
{
    if (other.root_ == nullptr)
        return;

    Node_ *new_root = copy(other.root_);
    root_ = new_root;

    size_ = other.size_;
    height_ = other.height_;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(BSTree &&other) noexcept // move ctor
: root_(other.root_), size_(other.size_), height_(other.height_)
{
    other.root_ = nullptr;
    other.size_ = 0;
    other.height_ = 0;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>& BSTree<T>::operator=(BSTree &&other) noexcept // move asign
{
    BSTree temp(std::move(other));
    swap(temp);

    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree &other) // copy assign
{
    if (this != &other)
    {
        BSTree temp(other); // get deep copy
        swap(temp);
    }

    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::is_empty() const noexcept
{
    return root_ == nullptr;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::is_balanced() const noexcept
{
    
}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::is_equals(const BSTree&) const noexcept
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
size_t BSTree<T>::get_size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
size_t BSTree<T>::get_height() const noexcept
{
    return height_;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::inorder_traversal() // симметричный (L-Root-R)
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::preorder_traversal() // прямой (Root-L-R) -- удобно для копирования
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::postorder_traversal() // обратный (L-R-Root) -- полезно при удалении
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::levelorder_traversal() // обход в ширину
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
const T* BSTree<T>::find(const T &f) const
{
    auto pointer = root_;

    if (pointer == nullptr) // дерево пустое
        return nullptr;

    while (pointer != nullptr)
    {
        if (pointer->data_ == f)
            return &(pointer->data_);

        if (f > pointer->data_) // идем вправо
            pointer = pointer->right_;
        else // идем влево
            pointer = pointer->left_;
    }

    return nullptr; // искомого элемента в дереве нет
}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::insert(const T &d)
{
    // insert должен вернуть true, если элемент был успешно добавлен, и false, если такой элемент уже был в дереве, дубликаты не вставляются.

    Node_ *parent = nullptr;
    auto pointer = root_;

    if (root_ == nullptr) // если дерево пустое создаем корень
    {
        root_ = new Node_(d);
        return true;
    }

    while (pointer != nullptr) // иначе идем по дереву
    {
        parent = pointer; // сохраняем значение ноды, чтобе иметь доступ, когда найдем место для вставки, ведь там указатель будет на nullptr

        if (d == pointer->data_) // не будем вставлять дубликаты
            return false;

        if (d > pointer->data_) // сравниваем с текущим эелементом
        {
            pointer = pointer->right_;

            if (pointer == nullptr)
            {
                parent->right_ = new Node_(d);
                return true;
            }
        }
        else
        {
            pointer = pointer->left_;

            if (pointer == nullptr)
            {
                parent->left_ = new Node_(d);
                return true;
            }
        }
    }

    return false;
}
//----------------------------------------------------------------------------------------------------
// template <typename T>
// bool BSTree<T>::replace(const Key &key, const T &v)
// {}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::erase(const T &key)
{ // Удалить узел с ключом key из BST, сохранив инвариант BST. Вернуть true, если удалили, и false, если ключа не было.

    auto link = root_;

    if (link == nullptr)
        return false;

    while (link != nullptr)
   {
        if (key == link->data_)
        {
           // как будто здесь надо сделать что-то, что должно перестроить дерево
           // то есть если этот ключ находится где-то посередине дерева, то как мы должны поступить?
            delete link;
            return true;
        }
        else if (key < link->data_) // left side
        {

        }
        else // right side
        {

        }
   }
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::clear()
{
    destroy_subtree(root_);
    root_ = nullptr;
    size_ = 0;
    height_ = 0;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::Node_* BSTree<T>::copy(const Node_ *temp)
{ // гарантия: либо скопировано всё дерево, либо не создано ничего.
    if (temp == nullptr)
        return nullptr;

    Node_ *new_node = new Node_(temp->data_);
    Node_ *left = nullptr;
    Node_ *right = nullptr;

    try
    {
        left = copy(temp->left_);
        right = copy(temp->right_);
    }
    catch (...) {
        destroy_subtree(left);
        destroy_subtree(right);
        delete new_node;
        throw;
    }

    new_node->left_ = left;
    new_node->right_ = right;

    return new_node;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::destroy_subtree(Node_ *temp) noexcept
{
    if (temp == nullptr)
        return;

    destroy_subtree(temp->left_);
    destroy_subtree(temp->right_);
    delete temp;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::swap(BSTree &t) noexcept
{
    std::swap(root_,t.root_);
    std::swap(size_ , t.size_);
    std::swap(height_ ,t.height_);
}
//----------------------------------------------------------------------------------------------------
