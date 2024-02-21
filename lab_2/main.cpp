#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "Array/Array.h"
#include "List/List.h"
#include "Data/Subcriber.h"


int main(int argc, char *argv[]) {
    /*  argc
        Целое число, содержащее количество аргументов, которые следуют в argv. Параметр argc всегда больше или равен 1

        argv
        argv[0] — всегда содержит строку, использованную для запуска программы (либо пустую строку)
        argv[1] — первый аргумент командной строки.
        Последний аргумент из командной строки имеет argv[argc - 1]argv[argc] значение NULL.
    */
    // argv[0]

    setlocale(LC_ALL, "ru_RU.UTF-8");
//    std::cout << "Hello, World!" << std::endl;

//    Subscriber A("Alice Stone");
//    Subscriber<List<Record> > B("Brian Steel");

    std::string line;
    std::ifstream file;

    const std::filesystem::path etc{"./Data"};

    for(auto const &dir_entry: std::filesystem::directory_iterator{etc}) {
        if (std::filesystem::is_directory(dir_entry)) {
            std::cout << dir_entry << '\n';
            auto fn = dir_entry.path() / std::string("Records.txt");
            if (std::filesystem::exists(fn)) {
                std::cout << fn << "is is_exists\n";
                // добавьте свой код открытия здесь

                file.open("Records.txt"); // окрываем файл для чтения
                if (file.is_open())
                {
                    std::cout << "File is opened" << std::endl;
                    while (std::getline(file, line))
                    {
                        std::cout << line << std::endl;
                    }
                }
                file.close();     // закрываем файл

                std::cout << "File is closed" << std::endl;

            }
        }
    }


    return 0;
}
