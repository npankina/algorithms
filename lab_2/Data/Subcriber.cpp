#include "Subcriber.h"


// class Subscriber
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont>::Subscriber(std::string name)
: Cypher(tool::subscribers_cypher++), Taken_Books(0), Name(name)
{}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont>::Subscriber(const Subscriber &lvalue) // copy ctor
{}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont>::Subscriber(Subscriber &&rvalue) // move ctor
{}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont> &Subscriber<Cont>::operator=(const Subscriber &lvalue) // copy assign
{}
//--------------------------------------------------------------------------------
template <typename Cont>
Subscriber<Cont> &Subscriber<Cont>::operator=(Subscriber &&rvalue) // move assign
{}
//--------------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Get_Lib_Data()
// TODO распечатать все элементы контейнера по шаблону вывода для Record
{}
//--------------------------------------------------------------------------------
template <typename Cont>
int Subscriber<Cont>::Get_First_Element_ID()
{}
//--------------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Set_Name(std::string name)
{}
//--------------------------------------------------------------------------------
template <typename Cont>
void Subscriber<Cont>::Add_Book(Record &&item)
{}
//--------------------------------------------------------------------------------
template <typename Cont>
bool Subscriber<Cont>::Replace_Book(const Record find, Record &&replace)
{}
//--------------------------------------------------------------------------------
template <typename Cont>
bool Subscriber<Cont>::Delete_Book(const Record item)
{}
//--------------------------------------------------------------------------------
template <typename Cont>
bool Subscriber<Cont>::Search_By_Cypher(int fnd)
{}
//--------------------------------------------------------------------------------
template <typename Cont>
bool Subscriber<Cont>::Search_By_Price(double fnd)
{}
//--------------------------------------------------------------------------------