#include "Array.h"

size_t Record::counter = 1000;
//--------------------------------------------------
Record::Record(size_t year, std::string name, std::string pub, double price)
: bookId_(counter++), yearOfPub_(year), bookName_(name), publisher_(pub), price_(price)
{}
//--------------------------------------------------





//--------------------------------------------------
size_t random_number(size_t min, size_t max)
{
    size_t num = min + rand() % (max - min + 1);
//    std::cout << "Rand number = " << num << " ";
    return num;
}
//--------------------------------------------------
double random_number_d(double min, double max)
{
    srand(time(NULL));

    double value;

    // получить случайное число как целое число с порядком precision
    value = rand() % (int)pow(10, 2);

    // получить вещественное число
    value = min + (value / pow(10, 2)) * (max - min);

    return value;
}
//--------------------------------------------------
bool Fill_Container(Array &obj, size_t size)
{
    srand(time(NULL)); // установка seed для ГСП

    for (size_t i = 0; i < size; ++i)
    {
//        obj.push_back(rec[random_number(0, 9)]);
        obj.push_back(Record());
    }
    return obj.size() == size;
}
//--------------------------------------------------
std::string random_pub()
{
    std::string arr[] = {"Pearson", "Oxford University", "Thomson-Reuters", "Alpina", "Exmo", "MIF", "Willey", "Addison Wesley"};
    return arr[random_number(0, 7)];
}
//--------------------------------------------------
std::string random_name()
{
    std::string arr[] = {"Algorithms", "Data Structures", "C++ Foreva", "C++", "Automata theory", "Discreete Math", "Graph Theory", "Programming Languages"};
    return arr[random_number(0, 7)];
}
//--------------------------------------------------
void Fill_Container_1(Array &obj, size_t arr_sz)
{
    for (int i = 0; i < arr_sz; ++i)
        obj.push_back({random_number(1999, 2023), random_name(), random_pub(), random_number_d(0.99, 100.00)});
}
//--------------------------------------------------
void Fill_Container_2(std::vector<Record> &obj, size_t arr_sz)
{
    for (int i = 0; i < arr_sz; ++i)
        obj.push_back({random_number(1999, 2023), random_name(), random_pub(), random_number_d(0.99, 100.00)});
}
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
: size_(other.size_), allocated_(other.allocated_), data_(other.data_)
{ // производим обнуление старого объекта
    other.data_ = nullptr;
    other.size_ = 0;
    other.allocated_ = 0;
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
bool Array::operator==(const Array &rhs) const
{
    bool flag = false;

    if (rhs.size_ == size_)
    {
        for (int i = 0; i < size_; ++i)
        {
            if ((rhs[i].bookId_ == data_[i].bookId_) and (rhs[i].price_ == data_[i].price_) and
                (rhs[i].publisher_ == data_[i].publisher_) and (rhs[i].bookName_ == data_[i].bookName_) and
                (rhs[i].yearOfPub_ == data_[i].yearOfPub_))
                flag = true;
            else
                return false;
        }
    }
    return flag;
}
//--------------------------------------------------
bool Array::operator!=(const Array &rhs) const
{
    bool flag = true;

    if (rhs.size_ == size_)
    {
        for (int i = 0; i < size_; ++i)
        {
            if ((rhs[i].bookId_ == data_[i].bookId_) and (rhs[i].price_ == data_[i].price_) and
                (rhs[i].publisher_ == data_[i].publisher_) and (rhs[i].bookName_ == data_[i].bookName_) and
                (rhs[i].yearOfPub_ == data_[i].yearOfPub_))
                flag = false;
            else
                return true;
        }
    }
    return flag;
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
    if (idx >= size_ or idx < 0)
        return false;
    return true;
}
//--------------------------------------------------
Array::reference Array::operator[](size_type index)
{
    if (index >= size_ or index < 0)
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

//    (data_ + size_)->~Record();
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
void Array::insert(size_type index, value_type &&value)
{// вставить элемент перед index
//#if for_test
    if ((index < 0) or (index > size_))
    {
        std::cout << "Error => Index out of range --- [insert method]" << std::endl;
        return;
    }
//#endif
#if prod
    if ((index < 0) or (index > allocated_))
        throw std::out_of_range("Error => Index out of range");
#endif

    if (size_ == allocated_)
        realloc(size_ * 2);

    for (int i = size_; i >= index; --i)
        data_[i + 1] = data_[i];
    data_[index] = value;
    ++size_;
}
//--------------------------------------------------
void Array::insert(iterator it, value_type &&value)
{}
//--------------------------------------------------
void Array::erase(size_type idx)
{
    if (idx < 0 || idx >= size_)
    {
//        throw std::out_of_range("index out of range");
        std::cout << "Error => Index out of range --- [erase method]" << std::endl;
        return;
    }

    for (int i = idx; i < size_-1; ++i)
        data_[i] = data_[i + 1];

    --size_;
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
size_t Array::linear_search_with_barier(int value) // последовательный поиск с барьером
{
    auto end = size_ - 1;
    if (size_ != 0) {
        auto last = data_[end]; //Сохраним прежний элемент массива
        data_[end] = value; //Гарантируем, что value есть в массиве
        //Есть гарантия того, что элемент есть в массиве, значит индекс можно не проверять
        size_t i = 0;
        for (; data_[i].yearOfPub_ != value; ++i) { //Одно условие в цикле
        }
        data_[end] = last; //Восстанавливаем последний элемент
        if (i != (end) || value == last.yearOfPub_) { //Не уткнулись в барьер или последний элемент был искомым
            return i;
        }
    }
    return std::numeric_limits<size_t>::max();
}
//--------------------------------------------------
int Array::linear_search(size_t key, std::string index)
{
    int i = 0, amount = 0;
    for (; i < size_; i++)
    {
        if (data_[i].yearOfPub_ == key)
        {
            ++amount;
            index += std::to_string(i); index += ", ";
//            std::cout << i << " ";
        }
    }
    return amount;
}
//--------------------------------------------------
int Array::linear_search(std::string key, std::string index)
{
    unsigned count{};       // количество вхождений
    for (int j = 0; j < size_; ++j)
    {
        for (unsigned i {}; i <= data_[j].bookName_.size();)
        {
            // получаем индекс
            size_t position = data_[j].bookName_.find(key, i);
            // если не найдено ни одного вхождения с индекса i, выходим из цикла
            if (position == std::string::npos) break;
            // если же вхождение найдено, увеличиваем счетчик вхождений
            ++count;
            // переходим к следующему индексу после position
            i = position + 1;
        }
    }
//    std::cout << "The word is found " << count << " times." << std::endl;
    return count;
}
//--------------------------------------------------
void Array::selection_sort(int x) // по году выпуска книги
{
    for (int j = 0; j < size_; ++j)
    {
        int min_idx = j;
        for (int i = j + 1; i < size_; ++i)
            if (data_[min_idx].yearOfPub_ > data_[i].yearOfPub_)
                min_idx = i;
        std::swap(data_[j], data_[min_idx]);
    }
}
//--------------------------------------------------
void Array::selection_sort(double x) // по году выпуска книги
{
    for (int j = 0; j < size_; ++j)
    {
        int min_idx = j;
        for (int i = j + 1; i < size_; ++i)
            if (data_[min_idx].price_ > data_[i].price_)
                min_idx = i;
        std::swap(data_[j], data_[min_idx]);
    }
}
//--------------------------------------------------
bool  Array::binary_search(int x)
{
    int min = 0, max = size_ - 1, mid = 0;
    while (min <= max)
    {
        mid = (min + max) / 2;
        if (data_[mid].yearOfPub_ == x)
            return true;
        if (data_[mid].yearOfPub_ < x)
            min = mid + 1;
        else
            max = mid - 1;
    }
    return false;
}
//--------------------------------------------------
bool  Array::binary_search(double x)
{
    int min = 0, max = size_ - 1, mid = 0;
    while (min <= max)
    {
        mid = (min + max) / 2;
        if (data_[mid].price_ == x)
            return true;
        if (data_[mid].price_ < x)
            min = mid + 1;
        else
            max = mid - 1;
    }
    return false;
}
//--------------------------------------------------
bool Array::interpolation_serch(int target)
{
    int min = 0, max = size_ - 1, pos = 0;
    while (min <= max)
    {
        pos = min + (((target - data_[min].yearOfPub_) * (max - min) ) / (data_[max].yearOfPub_ - data_[min].yearOfPub_) );

        if (pos < 0)
            return false;

        if (data_[pos].yearOfPub_ == target)
            return true;
        if (data_[pos].yearOfPub_ < target)
            min = pos + 1;
        else
            max = pos - 1;
    }
    return false;
}
//--------------------------------------------------
bool Array::interpolation_serch(double target)
{
    int min = 0, max = size_ - 1, pos = 0;
    while (min <= max)
    {
        pos = min + (((target - data_[min].price_) * (max - min) ) / (data_[max].price_ - data_[min].price_) );

        if (pos < 0)
            return false;

        if (data_[pos].price_ == target)
            return true;
        if (data_[pos].price_ < target)
            min = pos + 1;
        else
            max = pos - 1;
    }
    return false;
}
//--------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Array &rhs)
{
    for (int i = 0; i < rhs.size_; ++i)
    {
        os << "#" << i + 1 << '\n';
        os << "Catalog ID: " << rhs.data_[i].bookId_ << "\n";
        os << "Year of publishing: " << rhs.data_[i].yearOfPub_ << "\n";
        os << "Book name: " << rhs.data_[i].bookName_ << "\n";
        os << "Publisher: " << rhs.data_[i].publisher_ << "\n";
        os << "Price: " << rhs.data_[i].price_ << "\n\n";
    }

#if print
    os << "| ";

    for (size_t i = rhs.size_; i < rhs.allocated_; ++i)
        os << "#" << i + 1 << " " << rhs.data_[i].bookId_ << ' ';
#endif

    return os;
}