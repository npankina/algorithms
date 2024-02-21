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
TEST_CASE( "class Array: std::initializer_list 2" )
{
    // открыть файл Record.txt
    // прочитать построчно и сохранить в контейнер
    // закрыть файл

    std::string line;
    Array<Record> D;

    std::ifstream in("Record.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }
    in.close();     // закрываем файл

    Array<Record> D {};
    REQUIRE( D.empty() == false);
    REQUIRE( D.size() == 6);

    REQUIRE_THROWS_AS( D.erase(6), std::out_of_range);
    REQUIRE( D.size() == 6);

    int prev_size = D.size();
    D.erase(5);
    REQUIRE( D.size() == prev_size - 1 );
}
//--------------------------------------------------------------------------------




// class List
const int temp = 5;
//--------------------------------------------------------------------------------
TEST_CASE( "class List: default ctor", "[require]" )
{
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
TEST_CASE( "class List: find methods", "[require]" )
{
    List<int> W = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(W.is_element_exsist(5) == true);
//    auto it = W.find(5);
//    REQUIRE( == );

}
//--------------------------------------------------------------------------------


#if not_now
SCENARIO()
{
    GIVEN( "A vector with some items" )
    {
        Array<int> A;
        REQUIRE( A.empty() == true );
        REQUIRE( A.capacity() == A.size() + 10 );

        // проверить на выбрасывание исключений если индекс вне диапазона
        REQUIRE_THROWS_AS(A[0], std::out_of_range);
        REQUIRE_THROWS_AS(A[-1], std::out_of_range);


        WHEN( "the size is increased" )
        {
            A.realloc( 10 );

            THEN( "the size and capacity change" )
            {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
    }
}
#endif