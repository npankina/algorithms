/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */

#include "Subscriber.h"

//----------------------------------------------------------------------------------------------------
Subscriber::Subscriber(const std::string &name, uint64_t library_number, const std::string &registration_date);
: name_(name), library_number_(library_number), registration_date_(registration_date)
{}
//----------------------------------------------------------------------------------------------------
std::string Subscriber::Get_Name() const
{
    return name_;
}
//----------------------------------------------------------------------------------------------------
uint64_t Subscriber::Get_Library_Number() const noexcept
{
    return library_number_;
}
//----------------------------------------------------------------------------------------------------
std::string Subscriber::Get_Registration_Date() const
{
    return registration_date_;
}
//----------------------------------------------------------------------------------------------------
void Subscriber::Add_Book(const Book &book)
{
    auto it = std::find_if(books_.begin(), books_.end(), [&book](const Book& b) {
            // !!! Надо сделать
            // return b.getId() == book.getId();
        });
    if (it == books_.end())
        throw std::runtime_error("Book not found in the list");

    *it = book;
}
//----------------------------------------------------------------------------------------------------
void Subscriber::Replace_Book(const Book &book)
{
    // !!! Надо сделать!

    // throw std::runtime_error("Book not found in borrowed list.");
}
//----------------------------------------------------------------------------------------------------
void Subscriber::Remove_Book(const Book::key_t &book_id)
{
    auto it = std::remove_if(books_.begin(), books_.end(), [book_id](const Book& b)
    {
        return b.Get_Id() == book_id;
    });

    if (it == books_.end())
        throw std::runtime_error("Book not found in the list");

    books_.erase(it, books_.end());
}
//----------------------------------------------------------------------------------------------------
void Subscriber::Print_Books() const
{
    std::cout << "Books borrowed by " << name_ << ":" << std::endl;
    for (const auto& book : books_)
        book.Print();
}
//----------------------------------------------------------------------------------------------------