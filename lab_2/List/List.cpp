#include "List.h"


//--------------------------------------------------------------------------------
template <typename T>
std::ostream &operator<<(std::ostream &os, List<T> &list)
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
//--------------------------------------------------------------------------------




//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List()
: size_(0), head_(nullptr), tail_(nullptr)
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List(const std::initializer_list<value_type> &items, const T &value, const Alloc &alloc)
: size_(items.size() ), head_(nullptr), tail_(nullptr), alloc_(alloc)
{
    try
    {
        head_ = AllocTraits::allocate(alloc_, size_);
    }
    catch (std::bad_alloc &ba)
    {
        std::cout << "Fail to allocate memory for container." << std::endl;
        throw std::bad_alloc();
    }

    int i = 0;
    for (const auto &item : items)
    {
        AllocTraits::construct(alloc_, head_ + i, item);
        ++i;
    }
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List(const List &other) noexcept          // copy ctor
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::List(List &&other) noexcept              // move ctor
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc> &List<T, Alloc>::operator=(List &&other) noexcept // move assign
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc> &List<T, Alloc>::operator=(const List &other)     // copy assign
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::~List()
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::const_iterator List<T, Alloc>::begin() const noexcept
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::const_iterator List<T, Alloc>::end() const noexcept
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::begin() noexcept
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::end() noexcept
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::find(const_reference item) noexcept
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::const_iterator List<T, Alloc>::find(const Node &item) const noexcept
{
    return const_iterator(item);
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::reference List<T, Alloc>::front()
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::reference List<T, Alloc>::back()
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
bool List<T, Alloc>::empty() const noexcept
{
    return size_ == 0;
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
List<T, Alloc>::size_type List<T, Alloc>::size() const noexcept
{}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::push_front(const_reference rhs)
{ // добавить в начало
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::push_front(value_type &&tmp)
{ // добавить в начало - временный объект --

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::pop_front() noexcept
{ // удалить первый

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::push_back(const_reference obj)
{ // добавить в конец

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::push_back(value_type &&tmp)
{ // добавить в начало - временный объект --

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::pop_back() noexcept
{ // удалить последний

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::insert(const_iterator fnd, const_reference obj)
{ // вставить в позицию итератора

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::insert(iterator fnd, value_type &&tmp)
{ // вставить временный объект --

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::erase(const_iterator place) noexcept
{ // удалить указанный (в позиции)

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::swap(List &t) noexcept
{ // обменять с заданным списком
}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::clear() noexcept
{ // удалить все

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::clear(const_iterator it) noexcept
{ // удалить все начиная c позиции итератора

}
//--------------------------------------------------------------------------------
template <typename T, typename Alloc>
void List<T, Alloc>::copy(const List &obj)
{}
//--------------------------------------------------------------------------------