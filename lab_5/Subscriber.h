/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */

#pragma once
#include <string>
#include <vector>
#include "Book.h"

class Subscriber
{
public:
    Subscriber(const std::string &name, uint64_t library_number, const std::string &registration_date);

    // Получение данных
    std::string Get_Name() const;
    uint64_t Get_Library_Number() const noexcept;
    std::string Get_Registration_Date() const;

    void Add_Book(const Book &book); // Добавление книги
    void Replace_Book(const Book &book); // Замена книги
    void Remove_Book(const Book::key_t &book_id); // Удаление книги
    void Print_Books() const; // Печать списка книг

private:
    std::string name_;  // Фамилия абонента
    uint64_t library_number_;  // Библиотечный номер
    std::string registration_date_;  // Дата открытия карточки
    std::vector<Book> books_;  // Список взятых книг
};