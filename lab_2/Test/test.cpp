#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../Array.cpp"
#include <iostream>

// class Array
//--------------------------------------------------------------------------------
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

#if not_now
        WHEN( "the size is increased" )
        {
            A.realloc( 10 );

            THEN( "the size and capacity change" )
            {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
#endif
    }
}
//--------------------------------------------------------------------------------
TEST_CASE( "Exception std::out_of_range is true (fail)", "[require]" )
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
TEST_CASE( "Exception std::invalid_argument is true (fail)", "[require]" )
{
    Array<int> A;
    REQUIRE( A.empty() == true );
    REQUIRE_THROWS_AS(A.pop_back(), std::invalid_argument);

    A.push_back(2);
    A.push_back(5);

    REQUIRE( A.empty() == false );
    REQUIRE( A.size() == 2 );

    A.pop_back();
    REQUIRE( A.size() == 1 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "std::initializer_list" )
{
    Array<int> D{5,15, 97, 8, 21, 4};
}
//--------------------------------------------------------------------------------
TEST_CASE( "" )
{

}
//--------------------------------------------------------------------------------
