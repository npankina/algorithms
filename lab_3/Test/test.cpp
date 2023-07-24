#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

// #include "../Subscriber.cpp"
#include "../Array.cpp"
#include "../Config.cpp"


#if Subscr
Subscriber A("Alex"), B("Jane"), D("Ken");
//--------------------------------------------------
TEST_CASE( "id Generating", "[Subscriber ID]" )
{
    REQUIRE( A.Get_id() == "10000001" );
    REQUIRE( B.Get_id() == "10000002" );
    REQUIRE( D.Get_id() == "10000003" );
}
//--------------------------------------------------
TEST_CASE( "BooksCounter", "[Subscriber BooksCounter]" )
{
    REQUIRE( A.Get_BookCounter() == 0 );
    REQUIRE( B.Get_BookCounter() == 0 );
    REQUIRE( D.Get_BookCounter() == 0 );
}
//--------------------------------------------------
#endif


// Array classic
//--------------------------------------------------
TEST_CASE( "default ctor", "[default]" )
{
    Array A;
    REQUIRE( A.empty() == true );
    REQUIRE( A.capacity() == 10 );
}
//--------------------------------------------------
TEST_CASE( "explicit ctor", "[explicit]" )
{
    const int alloc = 15;
    Array B(alloc);

    REQUIRE( B.empty() == true );
    REQUIRE( B.capacity() == alloc );

    Array V(B);
    REQUIRE( V.size() == B.size() );
    REQUIRE( V.capacity() == B.capacity() );
    V.push_back(rec[0]);

    Array P(90);
    REQUIRE( P.empty() == true );
    REQUIRE( P.capacity() == 90 );
}
//--------------------------------------------------
TEST_CASE( "copy ctor", "[copy]" )
{
    const int alloc = 200;
    Array D(alloc);

    REQUIRE( D.empty() == true );
    REQUIRE( D.capacity() == alloc);

    Array U = D;
    REQUIRE( U.size() == D.size() );
    REQUIRE( U.capacity() == D.capacity() );
    D.push_back(rec[1]);
}
//--------------------------------------------------
TEST_CASE( "{} ctor", "[initialize ctor]" )
{
    Array D{rec[0], rec[1], rec[2]};
    REQUIRE( D.size() == 3 );
    REQUIRE( D.capacity() == 3);


    Array U = D;
    REQUIRE( U.size() == D.size() );
    REQUIRE( U.capacity() == D.capacity() );

    U.push_back(rec[3]);
    REQUIRE( U.size() == D.size() + 1 );

    Array W{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12},
            {2010, "C++ with Love", "Thomson-Reuters", 5.70},
            {2023, "Algorithms and data structures", "Oxford University", 7.24}};

    REQUIRE( W.empty() == false );
    W.push_back({2010, "C++ with Love", "Thomson-Reuters", 5.70});
    REQUIRE( W.capacity() == 10);

#if print
    std::cout << "{initialize} ctor\n";
    std::cout << D << std::endl;

    std::cout << "{initialize} ctor 2\n";
    std::cout << W << std::endl;
#endif
}
//--------------------------------------------------
TEST_CASE( "indexes access", "[indexes]" )
{
    Array D{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12}};
    REQUIRE(D.at(3) == false );
    REQUIRE(D.at(2) == true );
    REQUIRE(D.at(-1) == false );
}
//--------------------------------------------------
TEST_CASE( "push_back method", "[push_back method]" )
{
    Array A;
    A.push_back(rec[4]);
    REQUIRE( A.size() == 1 );
    REQUIRE( A.capacity() == 10 );
    REQUIRE( A.empty() == false );
}
//--------------------------------------------------
TEST_CASE( "realloc method", "[realloc method]" )
{
    Array A{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12}};

    REQUIRE( A.size() == 3 );
    REQUIRE( A.empty() == false );
    REQUIRE( A.capacity() == 3 );

    A.push_back({2023, "C++ the best lang", "Pearson", 4.99});

    // new momory is allocated
    REQUIRE( A.size() == 4 );
    REQUIRE( A.capacity() == 6 );
}
//--------------------------------------------------
TEST_CASE( "push_front method", "[push_front method]" )
{
    Array A{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12}};

    A.push_front({2023, "C++ the best lang", "Pearson", 4.99});
    REQUIRE( A.empty() == false );
    REQUIRE( A.size() == 4 );

    Array B = A;
    B.push_front({2022, "C++ 💜", "Pearson", 5.00});

    REQUIRE( B.empty() == false );
    REQUIRE( B.size() == 5 );
    REQUIRE( B.capacity() == 6 );

#if print
    std::cout << A << std::endl;
    std::cout << B << std::endl;
#endif
}
//--------------------------------------------------
TEST_CASE( "pop_back method", "[pop_back method]" )
{
    Array A{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12}};

    A.pop_back();
    REQUIRE( A.size() == 2 );


    Array B = A;
    B.pop_back();
    REQUIRE( B.size() == 1 );

#if print
    std::cout << A << std::endl;
    std::cout << B << std::endl;
#endif
}
//--------------------------------------------------
TEST_CASE( "pop_front method", "[pop_front method]" )
{
    Array A{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12}};

    A.pop_front();
    REQUIRE( A.size() == 2 );

    Array B = A;
    B.pop_front();
    REQUIRE( B.size() == 1 );

    B.clear();
    REQUIRE( B.empty() == true );
    REQUIRE( B.capacity() == 3 );

    B.pop_front();

#if print
    std::cout << A << std::endl;
    std::cout << B << std::endl;
#endif
}
//--------------------------------------------------
TEST_CASE( "erase method", "[erase method]" )
{
    Array W{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12},
            {2010, "C++ with Love", "Thomson-Reuters", 5.70},
            {2023, "Algorithms and data structures", "Oxford University", 7.24}};

    REQUIRE( W.size() == 5 );

    W.erase(0);
    REQUIRE( W.size() == 4 );

    W.erase(9);
    REQUIRE( W.size() == 4 );
}
//--------------------------------------------------
TEST_CASE( "insert method", "[insert method]" )
{
    Array W{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12},
            {2010, "C++ with Love", "Thomson-Reuters", 5.70}};

    REQUIRE( W.size() == 4 );

    W.insert(1, Record{2023, "Algorithms in C++", "Oxford University", 4.20});
    REQUIRE( W.size() == 5 );


    W.insert(8, Record{2021, "Data structures in C++", "Oxford University", 5.18});
    REQUIRE( W.size() == 5 );

#if print
    std::cout << W << std::endl;
#endif
}
//--------------------------------------------------
TEST_CASE( "bool == method", "[bool == method]" )
{
    Array A{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12}};

    REQUIRE( A.empty() == false );

    Array B = A;
    REQUIRE( (B == A) == true );
}
//--------------------------------------------------
TEST_CASE( "bool != method", "[bool != method]" )
{
    Array A{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "Postgres", "Thomson-Reuters", 3.12}};

    Array D;
    REQUIRE( (A != D) == true );

    Array B{{2020, "C++ programming", "Pearson", 9.99},
            {2019, "Databases", "Pearson", 8.75},
            {2017, "U", "Thomson-Reuters", 3.12}};

    REQUIRE( (B != A) == true );

    // равенство
    Array U(B);
    REQUIRE( (U != B) == false );

    Array Z = U;
    REQUIRE( (Z != U) == false );
}
//--------------------------------------------------
Array A{{2020, "C++ programming", "Pearson", 9.99},
        {2019, "Databases", "Pearson", 8.75},
        {2017, "Postgres", "Thomson-Reuters", 3.12},
        {2010, "C++ with Love", "Thomson-Reuters", 5.70},
        {2023, "Algorithms and data structures", "Oxford University", 7.24},
        {2023, "C++ the best lang", "Pearson", 4.99},
        {2022, "C++ 💜", "Pearson", 5.00},
        {2020, "Algorithms in C++", "Oxford University", 4.20},
        {2021, "Data structures in C++", "Oxford University", 5.18}};

TEST_CASE( "Linear Search with barier", "[linear_search_with_barier]" )
{
    std::string index = "";
    REQUIRE(A.linear_search(2020, index) == 2);
    REQUIRE(A.linear_search(1999, index) == 0);

    REQUIRE(A.linear_search("C++", index) == 6);
    REQUIRE(A.linear_search("C#", index) == 0);

    REQUIRE(A.linear_search_with_barier(2020) == 1);
    REQUIRE(A.linear_search_with_barier(2021) == 4);
}
//--------------------------------------------------
TEST_CASE( "Fill container", "[Random elements in container]" )
{
    Array U;
    REQUIRE( Fill_Container(U, 5) == true );
}
//--------------------------------------------------
TEST_CASE( "Binary Search method", "[Binary Search]" )
{
    A.selection_sort(1);
    REQUIRE(A.binary_search(2020) == true );
    REQUIRE(A.binary_search(2000) == false );
    REQUIRE(A.interpolation_serch(2020) == true );
    REQUIRE(A.interpolation_serch(2000) == false );
}
//--------------------------------------------------
TEST_CASE( "Interpolation Search method", "[Interpolation Search]" )
{
    A.selection_sort(0.0);
    REQUIRE(A.binary_search(9.99) == true );
    REQUIRE(A.binary_search(0.0) == false );
    REQUIRE(A.interpolation_serch(4.99) == true );
    REQUIRE(A.interpolation_serch(0.0) == false );
}