/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */

#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../Tree.cpp"

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