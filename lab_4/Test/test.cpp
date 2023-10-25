#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include "../List.h"

//--------------------------------------------------------------------------------
TEST_CASE( "default ctor", "[default ctor]" )
{
    List A;
    REQUIRE( A.empty() == true );
    REQUIRE( A.size() == 0 );
}
//--------------------------------------------------------------------------------
TEST_CASE( "initializer_list ctor", "[initializer_list]" )
{
    List B {Record{std::make_tuple(2020, "Berkly", 12.25)}, Record{std::make_tuple(2021, "Бином", 10.99)}};
    REQUIRE( B.empty() == false );
    REQUIRE( B.size() == 2);
}
//--------------------------------------------------------------------------------
TEST_CASE( "copy ctor", "[copy ctor]" )
{
    List C {Record{std::make_tuple(2020, "Berkly", 12.25)}, Record{std::make_tuple(2021, "Бином", 10.99)}};
    REQUIRE( C.size() == 2);

    List D(C);
    REQUIRE(D.size() == 2);
}
//--------------------------------------------------------------------------------
TEST_CASE( "move ctor", "[move ctor]" )
{
    List F = {Record{std::make_tuple(2020, "Berkly", 12.25)}};
    REQUIRE( F.empty() == false );
    REQUIRE( F.size() == 1);
}
//--------------------------------------------------------------------------------
TEST_CASE( "push_front() + pop_front()", "[push_front() && pop_front()]" )
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
TEST_CASE( "push_back() + pop_back()", "[push_fback() && pop_back()]" )
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
TEST_CASE( "clear()", "[clear()]" )
{
    List A;
    A.push_front(Record{std::make_tuple(2020, "Berkly", 12.25)});
    A.push_front(Record{std::make_tuple(2022, "Salmon", 32.99)});
    REQUIRE( A.empty() == false);
    REQUIRE( A.size() == 2);

    A.print();

    A.clear();
    REQUIRE( A.empty() == true);
}
//--------------------------------------------------------------------------------
TEST_CASE( "swap()", "[swap()]" )
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

    A.swap(B);
    REQUIRE( A.size() == 4 );
    REQUIRE( B.size() == 2);

}
//--------------------------------------------------------------------------------