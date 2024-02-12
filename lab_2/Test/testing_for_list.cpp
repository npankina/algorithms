#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../List/List.cpp"
#include <iostream>


//--------------------------------------------------------------------------------
TEST_CASE( "Exception std::out_of_range is true (fail)", "[require]" )
{
    List<int> A;
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
