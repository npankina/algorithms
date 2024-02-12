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