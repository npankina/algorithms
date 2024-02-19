#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../Data/Subcriber.cpp"
#include "../Array/Array.cpp"
#include "../List/List.cpp"
#include <iostream>



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
TEST_CASE( "class List: Exception std::bad_alloc is true (fail)", "[require]" )
{
//    List<int> A;
//    REQUIRE( A.empty() == true);
//
//    List<int> B{4, 5, 6, 7, 8};
//    REQUIRE( B.empty() == false);

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