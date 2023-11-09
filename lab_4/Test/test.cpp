#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../List.h"
#include "../Subcriber.h"

// class List включая class Record
//--------------------------------------------------------------------------------
TEST_CASE( "class List: default ctor", "[default ctor]" )
{
    List A;
    REQUIRE( A.empty() == true );
    REQUIRE( A.size() == 0 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: initializer_list ctor", "[initializer_list]" )
{
    List B {Record{std::make_tuple(2020, "Berkly", 12.25)}, Record{std::make_tuple(2021, "Бином", 10.99)}};
    REQUIRE( B.empty() == false );
    REQUIRE( B.size() == 2);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: copy ctor", "[copy ctor]" )
{
    List C {Record{std::make_tuple(2020, "Berkly", 12.25)}, Record{std::make_tuple(2021, "Бином", 10.99)}};
    REQUIRE( C.size() == 2);

    List D(C);
    REQUIRE(D.size() == 2);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: move ctor", "[move ctor]" )
{
    List F = {Record{std::make_tuple(2020, "Berkly", 12.25)}};
    REQUIRE( F.empty() == false );
    REQUIRE( F.size() == 1);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: push_front() + pop_front()", "[push_front() && pop_front()]" )
{
    List A;
    REQUIRE( A.empty() == true);

    A.push_front(Record{std::make_tuple(2020, "Berkly", 12.25)});
    REQUIRE( A.empty() == false);

    A.push_front(Record{std::make_tuple(2022, "Salmon", 32.99)});
    REQUIRE( A.size() == 2);

    A.pop_front();
    REQUIRE( A.size() == 1);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: push_back() + pop_back()", "[push_fback() && pop_back()]" )
{
    List A;
    REQUIRE( A.empty() == true);

    A.push_back(Record{std::make_tuple(2020, "Berkly", 12.25)});
    REQUIRE( A.empty() == false);

    A.push_back(Record{std::make_tuple(2022, "Salmon", 32.99)});
    REQUIRE( A.size() == 2);

    A.pop_back();
    REQUIRE( A.size() == 1);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: clear()", "[clear()]" )
{
    List A;
    A.push_front(Record{std::make_tuple(2020, "Berkly", 12.25)});
    A.push_front(Record{std::make_tuple(2022, "Salmon", 32.99)});
    REQUIRE( A.empty() == false);
    REQUIRE( A.size() == 2);

    A.clear();
    REQUIRE( A.empty() == true);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: swap()", "[swap()]" )
{
    List A;
    A.push_front(Record{std::make_tuple(2020, "Berkly", 12.25)});
    A.push_front(Record{std::make_tuple(2022, "Salmon", 32.99)});
    REQUIRE( A.empty() == false);
    REQUIRE( A.size() == 2);

    List B;
    B.push_back(Record{std::make_tuple(2020, "Berkly", 12.33)});
    B.push_back(Record{std::make_tuple(2021, "Brimsly", 95.50)});
    B.push_back(Record{std::make_tuple(2022, "Ostin", 122.30)});
    B.push_back(Record{std::make_tuple(2023, "Martin", 4.12)});

    REQUIRE( B.size() == 4);
    REQUIRE( (A.size() < B.size()) == true);

#if print
    std::cout << "Before SWAP \n";
    std::cout << "List A\n";
    std::cout << A << std::endl;
    std::cout << "List B\n";
    std::cout << B << std::endl;
#endif
    A.swap(B);
    REQUIRE( A.size() == 4 );
    REQUIRE( B.size() == 2);

#if print
    std::cout << "\nAfter SWAP \n";
    std::cout << "List A\n";
    std::cout << A << std::endl;
    std::cout << "List B\n";
    std::cout << B << std::endl;
#endif
}
//--------------------------------------------------------------------------------
TEST_CASE( "Merge Sort", "[merge Sort]" )
{
    List A;
    A.push_front(Record{std::make_tuple(2021, "A", 1.25)});
    A.push_front(Record{std::make_tuple(2020, "Bekly", 2.39)});
    A.push_front(Record{std::make_tuple(2022, "B", 2.25)});
    A.push_front(Record{std::make_tuple(2019, "D", 1.12)});
    A.push_front(Record{std::make_tuple(2018, "E", 1.99)});
    A.push_front(Record{std::make_tuple(2017, "F", 1.85)});
    A.push_front(Record{std::make_tuple(2016, "G", 3.25)});
    A.push_front(Record{std::make_tuple(2015, "H", 4.25)});
    A.push_front(Record{std::make_tuple(2014, "T", 3.99)});
    A.push_front(Record{std::make_tuple(2020, "Y", 1.33)});
    A.push_front(Record{std::make_tuple(2020, "W", 1.34)});
    A.push_front(Record{std::make_tuple(2020, "X", 1.35)});
    A.push_front(Record{std::make_tuple(2020, "S", 1.36)});
    A.push_front(Record{std::make_tuple(2020, "Z", 1.37)});
    A.push_front(Record{std::make_tuple(2020, "Q", 1.39)});
    A.push_front(Record{std::make_tuple(2020, "P", 1.38)});

    std::cout << A << std::endl;

    A = sort(A.begin(), A.end() );

    std::cout << A << std::endl;
}
//--------------------------------------------------------------------------------
TEST_CASE( "Shuffle", "[shuffle]" )
{
    List A;
    A.push_back(Record{std::make_tuple(2021, "A", 1.25)});
    A.push_back(Record{std::make_tuple(2020, "Bekly", 2.39)});
    A.push_back(Record{std::make_tuple(2022, "B", 2.25)});
    A.push_front(Record{std::make_tuple(2019, "D", 1.12)});
    A.push_front(Record{std::make_tuple(2018, "E", 1.99)});
    A.push_front(Record{std::make_tuple(2017, "F", 1.85)});
    A.push_front(Record{std::make_tuple(2016, "G", 3.25)});
    A.push_front(Record{std::make_tuple(2015, "H", 4.25)});
    A.push_front(Record{std::make_tuple(2014, "T", 3.99)});
    A.push_front(Record{std::make_tuple(2020, "Y", 1.33)});
    A.push_front(Record{std::make_tuple(2020, "W", 1.34)});
    A.push_front(Record{std::make_tuple(2020, "X", 1.35)});
    A.push_front(Record{std::make_tuple(2020, "S", 1.36)});
    A.push_front(Record{std::make_tuple(2020, "Z", 1.37)});
    A.push_front(Record{std::make_tuple(2020, "Q", 1.39)});
    A.push_front(Record{std::make_tuple(2020, "P", 1.38)});

    REQUIRE( A.size() == 16);
    A.shuffle_elements();
    REQUIRE( A.size() == 16);

//    std::cout << "List A AFTER shuffle" << std::endl;
//    std::cout << A << std::endl;
}
//--------------------------------------------------------------------------------



// class Subscriber
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: ctor", "[ctor]" )
{
    Subscriber A("Leonardo");
    A.add_book(Record{std::make_tuple(2020, "Berkly", 12.25)});

    REQUIRE(A.Get_Taken_Books() == 1);
    REQUIRE(A.Get_Name() == "Leonardo");
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: Set_Name()", "[Set_Name]" )
{
    Subscriber A;
    REQUIRE(A.Get_Name() == "");

    A.Set_Name("Donatello");
    REQUIRE(A.Get_Name() == "Donatello");
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: add_book()", "[add_book]" )
{
    Subscriber A;
    A.add_book(Record{std::make_tuple(2021, "A", 1.25)});
    A.add_book(Record{std::make_tuple(2022, "B", 2.25)});
    A.add_book(Record{std::make_tuple(2023, "C", 2.50)});
    A.add_book(Record{std::make_tuple(2019, "D", 10.12)});
    A.add_book(Record{std::make_tuple(2018, "E", 12.99)});
    A.add_book(Record{std::make_tuple(2017, "F", 1.85)});
    A.add_book(Record{std::make_tuple(2016, "G", 3.25)});
    A.add_book(Record{std::make_tuple(2015, "H", 4.25)});
    A.add_book(Record{std::make_tuple(2014, "T", 3.99)});
    A.add_book(Record{std::make_tuple(2020, "Y", 1.33)});
    A.add_book(Record{std::make_tuple(2020, "W", 1.34)});
    A.add_book(Record{std::make_tuple(2020, "X", 1.35)});
    A.add_book(Record{std::make_tuple(2020, "S", 1.36)});
    A.add_book(Record{std::make_tuple(2020, "Z", 1.37)});
    A.add_book(Record{std::make_tuple(2020, "Q", 1.39)});
    A.add_book(Record{std::make_tuple(2020, "P", 1.38)});

    REQUIRE( A.Get_Taken_Books() == 16 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: replace_book()", "[replace_book]" )
{
    Subscriber A;
    A.add_book(Record{std::make_tuple(2021, "A", 1.25)});
    A.add_book(Record{std::make_tuple(2022, "B", 2.25)});
    A.add_book(Record{std::make_tuple(2023, "C", 2.50)});
    A.add_book(Record{std::make_tuple(2019, "D", 10.12)});

    REQUIRE(A.replace_book(Record{std::make_tuple(2019, "D", 10.12)}, Record{std::make_tuple(2020, "Berkly", 12.25)}) == true);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: delete_book()", "[delete_book]" )
{
    Subscriber A;
    A.add_book(Record{std::make_tuple(2021, "A", 1.25)});
    A.add_book(Record{std::make_tuple(2022, "B", 2.25)});
    A.add_book(Record{std::make_tuple(2023, "C", 2.50)});
    A.add_book(Record{std::make_tuple(2019, "D", 10.12)});

    REQUIRE(A.Get_Taken_Books() == 4);
    REQUIRE(A.delete_book(Record{std::make_tuple(2019, "D", 10.12)}) == true);
    REQUIRE(A.Get_Taken_Books() == 3);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: search_by_cypher()", "[search_by_cypher]" )
{
    Subscriber A;
    A.add_book(Record{std::make_tuple(2021, "A", 1.25)});
    A.add_book(Record{std::make_tuple(2022, "B", 2.25)});
    A.add_book(Record{std::make_tuple(2023, "C", 2.50)});
    A.add_book(Record{std::make_tuple(2019, "D", 10.12)});

    REQUIRE(A.search_by_cypher(A.Get_First_Element_ID() ) == true);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: search_by_price()", "[search_by_price]" )
{
    Subscriber A;
    A.add_book(Record{std::make_tuple(2021, "A", 1.25)});
    A.add_book(Record{std::make_tuple(2022, "B", 2.25)});
    A.add_book(Record{std::make_tuple(2023, "C", 2.50)});
    A.add_book(Record{std::make_tuple(2019, "D", 10.12)});

    REQUIRE(A.search_by_price(1.25) == true);
}
//--------------------------------------------------------------------------------