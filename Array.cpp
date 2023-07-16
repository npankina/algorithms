#include "Array.h"


size_t Record::counter = 1000;
//--------------------------------------------------
Record::Record(size_t year, std::string name, std::string pub, double price) // set default value
: bookId_(counter++), yearOfPub_(year), bookName_(name), publisher_(pub), price_(price)
{}
//--------------------------------------------------



//--------------------------------------------------
Array::Array() : Array(10)
{}
//--------------------------------------------------
Array::Array(const size_type &alloc_size)
: allocated_(alloc_size), size_(0), data_(new value_type[allocated_])
{}
//--------------------------------------------------
Array::Array(const std::initializer_list<value_type> &t)
: allocated_(t.size()), size_(0), data_(new value_type[allocated_])
{
    for (auto i : t)
        push_back(i);
}
//--------------------------------------------------
Array::Array(const Array &other) // copy ctor
: size_(other.size_), allocated_(other.allocated_), data_(new value_type[allocated_])
{
    std::copy(other.data_,  other.data_ + size_, data_);
}
//--------------------------------------------------
Array::Array(Array &&other) noexcept // move ctor
: size_(other.size_), allocated_(other.allocated_), data_(new value_type[allocated_])
{
    std::swap(size_, other.size_);
    std::swap(allocated_, other.allocated_);
    std::swap(data_, other.data_);
}
//--------------------------------------------------
Array &Array::operator=(const Array &other) // copy assignment
{// !!! внести изменения - можно написать его лучше
    if (this != &other)
    {
        size_ = other.size_;
        allocated_ = other.allocated_;
        delete[] data_;
        data_ = new value_type[allocated_];
        std::copy(data_, data_ + size_, other.data_);
    }
    return *this;
}
//--------------------------------------------------
Array &Array::operator=(Array &&other) noexcept // move assign
{
    if (this != &other)
    {
        std::swap(size_, other.size_);
        std::swap(allocated_, other.allocated_);
        std::swap(data_, other.data_);
    }
    return *this;
}
//--------------------------------------------------
Array::~Array() noexcept
{
    delete[] data_;
}
//--------------------------------------------------
size_t Array::size() const noexcept
{
    return size_;
}
//--------------------------------------------------
bool Array::empty() const noexcept
{
    return size_ == 0;
}
//--------------------------------------------------
size_t Array::capacity() const noexcept
{
    return allocated_;
}
//--------------------------------------------------
Array::iterator Array::begin() noexcept
{
    return data_;
}
//--------------------------------------------------
Array::const_iterator Array::cbegin() const noexcept
{
    return data_;
}
//--------------------------------------------------
Array::iterator Array::end() noexcept
{
    return data_ + size_;
}
//--------------------------------------------------
Array::const_iterator Array::cend() const noexcept
{
    return data_ + size_;
}
//--------------------------------------------------
void Array::realloc(size_type new_capacity)
{
    // 1. Allocate a new block of memory
    // 2. copy / move old elements into new block
    // 3. delete old block

    auto *new_block = new value_type[new_capacity];

    if (new_capacity < size_)
        size_ = new_capacity;

    for (size_t i = 0; i < size_; i++)
        new_block[i] = std::move(data_[i]);

    delete [] data_;
    data_ = new_block;
    allocated_ = new_capacity;
}
//--------------------------------------------------
bool Array::at(size_t idx) const noexcept
{
    if (idx < size_ )
        return true;
    return false;
}
//--------------------------------------------------
Array::reference Array::operator[](size_type index)
{
    if (index >= size_)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
}
//--------------------------------------------------
Array::const_reference Array::operator[](size_type index) const
{
    if (index >= size_)
        throw std::out_of_range("Error => index out of range");
    return data_[index];
}
//--------------------------------------------------
Array::reference Array::front() noexcept
{
    return data_[0];
}
//--------------------------------------------------
Array::const_reference Array::front() const noexcept
{
    return data_[0];
}
//--------------------------------------------------
Array::reference Array::back() noexcept
{
    return data_[size_ - 1];
}
//--------------------------------------------------
Array::const_reference Array::back() const noexcept
{
    return data_[size_ - 1];
}
//--------------------------------------------------
void Array::push_back(const value_type& value)
{
    if (allocated_ == size_)
        realloc(allocated_ * 2); // или (allocated_ + allocated_ / 2)

    data_[size_] = value;
    ++size_;
}
//--------------------------------------------------
void Array::pop_back() noexcept
{
    if(size_ == 0) return; // по-хорошему здесь нужно бросить исключение, но метод по условию noexcept

    (data_ + size_)->~Record();
    --size_;
}
//--------------------------------------------------
void Array::push_front(const value_type& v)
{
    if (size_ == 0)
        push_back(v);
    else
    {
        if (size_ == allocated_)
            realloc(allocated_ * 2);

        for (size_t i = size_; i > 0; i--)
            data_[i] = data_[i - 1];

        data_[0] = v;
        ++size_;
    }
}
//--------------------------------------------------
void Array::pop_front() noexcept
{
    if (size_ == 0)
    {
        std::cout << "Error => the array is empty --- [pop_front method]" << std::endl;
        return;
    }

    for (int i = 0; i < size_-1; i++)
        data_[i] = data_[i + 1];

    --size_;
}
//--------------------------------------------------
void Array::insert(size_type idx)
{}
//--------------------------------------------------
void Array::insert(iterator it)
{}
//--------------------------------------------------
void Array::erase(size_type idx)
{
    if (idx < 0 || idx >= size_)
        throw std::out_of_range("index out of range");

    for (int i = idx; i < size_-1; i++)
        data_[i] = data_[i + 1];

    --size_;
}
//--------------------------------------------------
void Array::erase(iterator it)
{
    if (it < begin() || it >= end())
        throw std::out_of_range("index out of range");
    size_type index = it - begin();
    erase(index);
}
//--------------------------------------------------
void Array::clear() noexcept
{
    size_ = 0;
}
//--------------------------------------------------
void Array::swap(Array &rhs)
{
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(allocated_, rhs.allocated_);
}
//--------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Array &rhs)
{
    for (int i = 0; i < rhs.size_; ++i)
    {
        os << "\nCatalog ID: " << rhs.data_[i].bookId_ << "\n";
        os << "Year of publishing: " << rhs.data_[i].yearOfPub_ << "\n";
        os << "Book name: " << rhs.data_[i].bookName_ << "\n";
        os << "Publisher: " << rhs.data_[i].publisher_ << "\n";
        os << "Price: " << rhs.data_[i].price_ << "\n";
    }
    return os;
}
