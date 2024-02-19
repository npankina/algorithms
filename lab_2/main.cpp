#include <iostream>
#include "Array/Array.h"
#include "List/List.h"
#include "Data/Subcriber.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Subscriber A("Alice Stone");
    Subscriber<List<Record> > B("Brian Steel");

    return 0;
}
