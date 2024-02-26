#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../Data/Subcriber.cpp"
#include "../Array/Array.cpp"
#include "../List/List.cpp"
#include <iostream>
#include <fstream>


// class Array
//--------------------------------------------------------------------------------
TEST_CASE( "class Array: Exception std::out_of_range is true (fail)", "[require]" )
{
    Array<int> A;
    REQUIRE( A.empty() == true );
    REQUIRE_THROWS_AS(A[0], std::out_of_range);
    REQUIRE_THROWS_AS(A[-1], std::out_of_range);

    A.push_back(2);
    A.push_back(5);

    REQUIRE( A.empty() == false );
    REQUIRE( A.size() == 2 );

    REQUIRE_THROWS_AS(A[3], std::out_of_range);
    REQUIRE_THROWS_AS(A[-1], std::out_of_range);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Array: Exception std::invalid_argument (fail) : pop_front(), pop_back()", "[require]" )
{
    Array<int> A;
    REQUIRE( A.empty() == true );
    REQUIRE_THROWS_AS(A.pop_back(), std::invalid_argument);
    REQUIRE_THROWS_AS(A.pop_front(), std::invalid_argument);

    A.push_back(2);
    A.push_back(5);

    REQUIRE( A.empty() == false );
    REQUIRE( A.size() == 2 );

    A.pop_back();
    REQUIRE( A.size() == 1 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Array: pop_front()", "[require]" )
{
    Array<int> A;
    REQUIRE( A.empty() == true );
    REQUIRE_THROWS_AS(A.pop_back(), std::invalid_argument);
    REQUIRE_THROWS_AS(A.pop_front(), std::invalid_argument);

    A.push_back(2);
    A.push_back(5);

    REQUIRE( A.empty() == false );
    REQUIRE( A.size() == 2 );

    A.pop_back();
    REQUIRE( A.size() == 1 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Array: std::initializer_list" )
{
    Array<int> D { 5,15, 97, 8, 21, 4 };
    REQUIRE( D.empty() == false);
    REQUIRE( D.size() == 6);

    REQUIRE_THROWS_AS( D.erase(6), std::out_of_range);
    REQUIRE( D.size() == 6);

    int prev_size = D.size();
    D.erase(5);
    REQUIRE( D.size() == prev_size - 1 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Array: erase(size_type index)" )
{
    Array<int> D { 5, 15, 97, 8, 21, 4 };
    int prev_size = D.size();

    REQUIRE_THROWS_AS( D.erase(6), std::out_of_range);
    REQUIRE( D.size() == 6);

    D.erase(5);
    REQUIRE( D.size() == prev_size - 1 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "class Array: swap(Array &rhs)" )
{
    Array<int> A;
    Array<int> D { 5, 15, 97, 8, 21, 4 };

    int size_D = D.size();
    REQUIRE( A.empty() == true);
    A.swap(D);
    REQUIRE( A.size() == size_D);
    REQUIRE( D.empty() == true);
}
//--------------------------------------------------------------------------------




// class List
//--------------------------------------------------------------------------------
TEST_CASE( "class List: default ctor", "[require]" )
{
    const int temp = 5;
    List<int> A;
    REQUIRE(A.is_empty() == true);

    A.push_back(8);
    REQUIRE(A.is_empty() == false);
    REQUIRE(A.size() == 1);

    A.push_back(temp);
    REQUIRE(A.size() == 2);

    A.push_front(9);
    A.push_front(temp);
    REQUIRE(A.size() == 4);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: inializer_list ctor", "[require]" )
{
    const int temp = 5;
    List<int> A{3, 4, 5, 8, 10};
    REQUIRE(A.is_empty() == false);
    REQUIRE(A.size() == 5);

    // push_back
    A.push_back(5);
    A.push_back(temp);

    REQUIRE(A.size() == 7);

    // push_front
    A.push_front(9);
    A.push_front(temp);

    const int size = 9;
    REQUIRE(A.size() == size);

    // copy ctor
    List<int> B = A;
    REQUIRE(B.size() == size);

    // copy assign
    List<int> C(B);
    REQUIRE(C.size() == size);

    // move assign
    List<int> D = std::move(C);
    REQUIRE(D.size() == size);

    // move ctor
    List<int> F(std::move(D));
    REQUIRE(F.size() == size);

    List<int> W = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(W.size() == 10);

    W.swap(F);
    REQUIRE(F.size() == 10);
    REQUIRE(W.size() == size);

    W.clear();
    REQUIRE(W.is_empty() == true);
}
//--------------------------------------------------------------------------------
TEST_CASE( "class List: find, erase methods", "[require]" )
{
    List<int> W = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(W.is_element_exsist(5) == true);
    REQUIRE(W.erase(5) == true);
    REQUIRE(W.size() == 9);
}
//--------------------------------------------------------------------------------




// class Record
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

    REQUIRE( A.Search_By_Price(1.25) == true); // 3.99
    REQUIRE( A.Search_By_Price(3.99) == true);
}
//--------------------------------------------------------------------------------