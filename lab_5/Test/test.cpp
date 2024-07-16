#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../Plain_Tree.cpp"

// class Tree
//--------------------------------------------------------------------------------
TEST_CASE( "class Tree: default ctor", "[default ctor]" )
{
    Tree<int> A;
    REQUIRE( A.Size() == 0 );

    A.Insert(100);

    REQUIRE( A.Size() == 1 );
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------