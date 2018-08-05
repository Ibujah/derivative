#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include "../basic_operands/Integers.hpp"
#include "../basic_operands/Arguments.hpp"
#include "../basic_operations/List_Op_Comm.hpp"

template<typename F>
struct FilterInt {
	using type = F;
};

template<typename OpCom, char symb, unsigned int n1, unsigned int n2, bool b1, bool b2>
struct FilterInt<List_Op_Comm<OpCom,symb,Integer<n1,b1>,Integer<n2,b2> > >
{
	using type = typename OpCom::template OpInt<Integer<n1,b1>,Integer<n2,b2> >::type;
};

template<typename OpCom, char symb, unsigned int n1, unsigned int n2, bool b1, bool b2, typename O, typename... Ops>
struct FilterInt<List_Op_Comm<OpCom,symb,Integer<n1,b1>,Integer<n2,b2>,O,Ops...> >
{
	using type = typename FilterInt<List_Op_Comm<OpCom,symb,typename OpCom::template OpInt<Integer<n1,b1>,Integer<n2,b2> >::type,O,Ops...> >::type;
};

template<typename O>
struct FilterIntRec
{
	using type = typename FilterInt<typename O::template apply_rec<FilterInt>::type>::type;
};


template<typename F>
struct FilterArgs {
	using type = F;
};

template<typename OpCom, char symb, unsigned int n, bool b, typename O, typename... Ops>
struct FilterArgs<List_Op_Comm<OpCom,symb,Integer<n,b>,O,Ops... > >
{
	using next = typename FilterArgs<List_Op_Comm<OpCom,symb,O,Ops... > >::type;
	using type = typename List_Op_Comm<OpCom,symb,Integer<n,b> >::template append<next>::type;
};

template<unsigned int n, typename... Ops>
struct FilterArgs<List_Op_Comm<OpPlus,'+',Argument<n>,Argument<n>,Ops... > >
{
	using type = typename FilterArgs<List_Op_Comm<OpPlus,'+',Mult<Integer<2>,Argument<n> >,Ops... > >::type;
};

template<unsigned int n1, unsigned int n, typename... Ops>
struct FilterArgs<List_Op_Comm<OpPlus,'+',Mult<Integer<n1>,Argument<n> >,Argument<n>,Ops... > >
{
	using type = typename FilterArgs<List_Op_Comm<OpPlus,'+',Mult<Integer<n1+1>,Argument<n> >,Ops... > >::type;
};

template<typename O>
struct FilterArgsRec
{
	using type = typename FilterArgs<typename O::template apply_rec<FilterArgs>::type>::type;
};


#endif //_SIMPLIFY_H_

