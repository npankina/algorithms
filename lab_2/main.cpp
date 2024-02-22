#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include <boost/algorithm/string.hpp>

#include "Array/Array.h"
#include "List/List.h"
#include "Data/Subcriber.h"


void get_files(std::vector<std::string> &paths, const std::string &current_path)
{ // рекурсивно выводит список всех файлов в каталогах переданного пути

    for (const auto &file : std::filesystem::directory_iterator(current_path) )
    {
        if (std::filesystem::is_directory(file))
            get_files(paths, file.path().string() );
        else
            paths.push_back(file.path().string() );
    }

    int i;
    for (i = 0; i < paths.size(); i++)
        std::cout << paths[i] << std::endl;

#if for_test
    std::cout << "Всего строк - " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
#endif
}

//template <typename T>
void copy_elements_from_txt_to_container(std::string directory, std::vector<Record> &cont)
{ /* директория должна быть абсолютный путь до файла
 *   контейнер должен иметь метод push_back()
 * */
    std::vector<std::string> results;
    std::string line;
    std::ifstream file;

    file.open(directory); // окрываем файл для чтения
    if (file.is_open())
    {
        std::cout << "File is opened" << std::endl;
        while (std::getline(file, line))
        {
//            std::cout << "\nThis is print 'line'\n";
//            std::cout << line << std::endl;
            boost::split(results, line, [](char c){return c == ',';});
//            std::cout << "This is print 'vector'\n";
            for(int i = 0; i < results.size(); i++)
            {
//                if (results[i] == ' ')
//                    results.erase(i,1);
                std::cout << results[i] << std::endl;
            }

//                auto t = std::make_tuple<>;
        }
//        std::cout << std::endl;
    }
    file.close();     // закрываем файл

    std::cout << "File is closed" << std::endl;
}

int main(int argc, char *argv[]) {
    /*  argc
        Целое число, содержащее количество аргументов, которые следуют в argv. Параметр argc всегда больше или равен 1

        argv
        argv[0] — всегда содержит строку, использованную для запуска программы (либо пустую строку)
        argv[1] — первый аргумент командной строки.
        Последний аргумент из командной строки имеет argv[argc - 1]argv[argc] значение NULL.
    */

    setlocale(LC_ALL, "ru_RU.UTF-8");
#if for_test_2
    std::cout << "Hello, World!" << std::endl;

    Subscriber A("Alice Stone");
    Subscriber<List<Record> > B("Brian Steel");

    std::vector<std::string> paths;
    get_files(paths, ".");
#endif

    std::vector<Record> Rec;

    copy_elements_from_txt_to_container("/Users/dev/Projects/CLionProjects/algorithms/lab_2/Data/Records.txt", Rec);

#if here
    const std::filesystem::path etc{"/Users/dev/Projects/CLionProjects/algorithms/lab_2/Data/"};

    for (auto const &dir_entry: std::filesystem::directory_iterator{etc}) {
        if (std::filesystem::is_directory(dir_entry)) {
            std::cout << dir_entry << '\n';
            auto fn = dir_entry.path() / std::string("Records.txt");
            if (std::filesystem::exists(fn)) {
                std::cout << fn << "is is_exists\n";
                // добавьте свой код открытия здесь



            }
        }
    }

#endif

    return 0;
}
