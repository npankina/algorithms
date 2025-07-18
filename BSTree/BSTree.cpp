#include "BSTree.h"
#include "BSTree.h"


//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(void) : root_(nullptr)
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::~BSTree(void)
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
BSTree<T>::BSTree(const T &d) : root_(new Node_(d))
{}
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
{}
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
size_t BSTree<T>::count() const noexcept
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
size_t BSTree<T>::height() const noexcept
{}
//----------------------------------------------------------------------------------------------------
// template <typename T>
// T BSTree<T>::find(const Key &key) const
// {}
// //----------------------------------------------------------------------------------------------------
// template <typename T>
// bool BSTree<T>::insert(const Key &key, const T &v)
// {}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool BSTree<T>::insert(const T &d)
{
    // insert должен вернуть true, если элемент был успешно добавлен, и false, если такой элемент уже был в дереве.

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
// //----------------------------------------------------------------------------------------------------
// template <typename T>
// bool BSTree<T>::erase(const Key &key)
// {}
// //----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::clear()
{}
//----------------------------------------------------------------------------------------------------
template <typename T>
void BSTree<T>::swap(BSTree &t) noexcept
{}
//----------------------------------------------------------------------------------------------------
