//#include "Subcriber.h"
//
//
//// class Subscriber
////--------------------------------------------------------------------------------
//Subscriber::Subscriber(std::string name)
//: Last_Name(name), Taken_Books(0), Cypher(tool::subscribers_cypher++)
//{}
////--------------------------------------------------------------------------------
//Subscriber::Subscriber(const Subscriber &lhs)
//: Last_Name(lhs.Last_Name), Taken_Books(lhs.Taken_Books), Cypher(lhs.Cypher)
//{
////     Library_Data = lhs.Library_Data; // выxзовется copy ctor
//// TODO
//}
////--------------------------------------------------------------------------------
//Subscriber::Subscriber(Subscriber &&rhs)
//: Last_Name(std::move(rhs.Last_Name)), Taken_Books(std::move(rhs.Taken_Books)), Cypher(std::move(rhs.Cypher))
//{
//    Library_Data = std::move(rhs.Library_Data);
//}
////--------------------------------------------------------------------------------
//Subscriber &Subscriber::operator=(const Subscriber &lhs)
//{
//    if (&lhs != this)
//    {
//        Last_Name = lhs.Last_Name;
//        Taken_Books = lhs.Taken_Books;
//        Cypher = lhs.Cypher;
////        Library_Data = lhs.Library_Data;
//    }
//    return *this;
//}
////--------------------------------------------------------------------------------
//Subscriber &Subscriber::operator=(Subscriber &&rhs)
//{
//    if (&rhs != this)
//    {
//        std::swap(Last_Name, rhs.Last_Name);
//        std::swap(Taken_Books, rhs.Taken_Books);
//        std::swap(Cypher, rhs.Cypher);
////        Library_Data.swap(rhs.Library_Data);
//    }
//    return *this;
//}
////--------------------------------------------------------------------------------
//void Subscriber::Get_Lib_Data()
//{
////    std::cout << Library_Data << std::endl;
//}
////--------------------------------------------------------------------------------
//void Subscriber::Set_Name(std::string name)
//{
//    Last_Name = name;
//}
////--------------------------------------------------------------------------------
//void Subscriber::Add_Book(Record &&item)
//{
//    Library_Data.push_back(item);
//    ++Taken_Books;
//}
////--------------------------------------------------------------------------------
//#if todo_methods
//int Subscriber::Get_First_Element_ID()
//{
//    return (*lib_data.begin() ).data_.Get_cypher();
//}
////--------------------------------------------------------------------------------
//bool Subscriber::replace_book(const Record fnd, Record &&replace)
//{
//    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
//    {
//        if ( (*it).data_.Get_publisher() == fnd.Get_publisher() )
//        {
//            lib_data.erase(it); // удалить старый элемент
//            lib_data.push_front(replace);
//            return true;
//        }
//    }
//    return false;
//}
////--------------------------------------------------------------------------------
//bool Subscriber::delete_book(const Record item)
//{
//    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
//    {
//        if ( (*it).data_.Get_publisher() == item.Get_publisher() )
//        {
//            lib_data.erase(it);
//            --Taken_Books;
//            return true;
//        }
//    }
//    return false;
//}
////--------------------------------------------------------------------------------
//bool Subscriber::search_by_cypher(int item)
//{
//    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
//        if ( (*it).data_.Get_cypher() == item)
//            return true;
//    return false;
//}
////--------------------------------------------------------------------------------
//bool Subscriber::search_by_price(double fnd)
//{
//    for (auto it = lib_data.begin(); it != lib_data.end(); ++it)
//        if ( (*it).data_.Get_price_() == fnd)
//            return true;
//    return false;
//}
////--------------------------------------------------------------------------------
//#endif