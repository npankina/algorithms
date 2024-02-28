#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../Data/Subcriber.cpp"
#include "../List.cpp"

//--------------------------------------------------------------------------------
std::vector<Record> Z
{
        Record(std::make_tuple(2021, "Berkly", 1.25)),
        Record(std::make_tuple(2022, "Mellon University", 2.25)),
        Record(std::make_tuple(2023, "Berkly", 2.50)),
        Record(std::make_tuple(2019, "Columbia University Press", 1.12)),
        Record(std::make_tuple(2018, "Cisco Press", 1.99)),
        Record(std::make_tuple(2017, "HarperCollins", 1.85)),
        Record(std::make_tuple(2016, "Berkly", 3.25)),
        Record(std::make_tuple(2015, "Columbia University Press", 4.25)),
        Record(std::make_tuple(2014, "Remington & Co", 3.99)),
        Record(std::make_tuple(2011, "Remington & Co", 1.34)),
        Record(std::make_tuple(2010, "Remington & Co", 1.33)),
        Record(std::make_tuple(2012, "Berkly", 1.35)),
        Record(std::make_tuple(2013, "HarperCollins", 1.36)),
        Record(std::make_tuple(2017, "O'relly", 1.37))
};
//--------------------------------------------------------------------------------




//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: Add_Book()", "[require]" )
{
    Subscriber<List<Record>> A("Alice Miller");
    REQUIRE(A.Get_Taken_Books() == 0);
    A.Add_Book(Z[0]);
    REQUIRE(A.Get_Taken_Books() == 1);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: Replace_Book()", "[require]" )
{
    Subscriber<List<Record>> A("Alice Miller");
    REQUIRE(A.Get_Taken_Books() == 0);
    A.Add_Book(Z[0]);
    REQUIRE(A.Get_Taken_Books() == 1);
//    A.Get_Lib_Data();

    A.Replace_Book(0, Z[1]);
    REQUIRE(A.Get_Taken_Books() == 1);
//    A.Get_Lib_Data();

    A.Add_Book(Z[2]);
    REQUIRE(A.Get_Taken_Books() == 2);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: Search_By_Cypher", "[require]" )
{
    Subscriber<List<Record>> A("Alice Miller");
    for (int i = 0; i < Z.size(); i++)
        A.Add_Book(Z[i]);
    REQUIRE(A.Get_Taken_Books() == Z.size() );
//    A.Get_Lib_Data();

    REQUIRE( A.Search_By_Cypher(10000005) == true );
    REQUIRE( A.Search_By_Cypher(10000013) == true );
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Subscriber: Search_By_Price", "[require]" )
{
    Subscriber<List<Record>> A("Alice Miller");
    for (int i = 0; i < Z.size(); i++)
        A.Add_Book(Z[i]);
    REQUIRE(A.Get_Taken_Books() == Z.size() );
//    A.Get_Lib_Data();

    REQUIRE( A.Search_By_Price(1.25) == true);
    REQUIRE( A.Search_By_Price(3.99) == true);
}
//--------------------------------------------------------------------------------