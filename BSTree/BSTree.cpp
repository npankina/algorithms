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
    if (t.empty())
        return;

    for (auto it = t.begin(), end = t.end(); it != end; ++it)
        insert(*it);
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(const BSTree &other) // copy ctor
{
    size_ = other.size_;
    height_ = other.height_;

    root_ = new Node_();
    root_.copy(other);
}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(BSTree &&other) noexcept // move ctor
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>& BSTree<T>::operator=(BSTree &&other) noexcept // move asign
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree &other) // copy assign
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::empty() const noexcept
{
    return root_ == nullptr;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
size_t BSTree<T>::size() const noexcept
{
    return size_;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
size_t BSTree<T>::height() const noexcept
{
    return height_;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::in_order()
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

        if (f >= pointer->data_) // идем вправо
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
}
//----------------------------------------------------------------------------------------------------
// template <typename T>
// bool BSTree<T>::replace(const Key &key, const T &v)
// {}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::erase(const T &key)
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::clear()
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::copy()
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::swap(BSTree &t) noexcept
{}
//----------------------------------------------------------------------------------------------------
