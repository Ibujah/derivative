#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include "../basic_operands/Integers.hpp"
#include "../basic_operands/Arguments.hpp"
#include "../basic_operations/List_Op_Comm.hpp"
#include "Sort.hpp"
#include "RemoveOp.hpp"

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


template<typename F>
struct FilterPlus {
	using type = F;
};

template<typename O1, typename O2, typename... Ops>
struct FilterPlus<Plus<O1,O2,Ops... > >
{
	using next = typename FilterPlus<Plus<O2,Ops... > >::type;
	using type = typename Plus<O1>::template append<next>::type;
};

template<typename O>
struct FilterPlus<Plus<Zero,O> >
{
	using type = O;
};

template<typename O, typename... Ops>
struct FilterPlus<Plus<Zero,O,Ops...> >
{
	using type = typename FilterPlus<Plus<O,Ops...> >::type;
};

template<typename O>
struct FilterPlusRec
{
	using type = typename FilterPlus<typename O::template apply_rec<FilterPlus>::type>::type;
};


template<typename F>
struct FilterMult {
	using type = F;
};

template<typename O2, typename... Ops>
struct FilterMult<Mult<Zero,O2,Ops...> >
{
	using type = Zero;
};

template<typename O>
struct FilterMult<Mult<One,O> >
{
	using type = O;
};

template<typename O1, typename O2, typename... Ops>
struct FilterMult<Mult<O1,O2,Ops... > >
{
	using next = typename FilterMult<Mult<O2,Ops... > >::type;
	using type = typename Mult<O1>::template append<next>::type;
};

template<typename O, typename... Ops>
struct FilterMult<Mult<One,O,Ops...> >
{
	using type = typename FilterMult<Mult<O,Ops...> >::type;
};


template<typename O>
struct FilterMultRec
{
	using type = typename FilterMult<typename O::template apply_rec<FilterMult>::type>::type;
};


template<typename O>
struct Simp
{
	using s1 = typename RemOpRec<O>::type;
	using s2 = typename SortRec<s1>::type;
	using s3 = typename FilterIntRec<s2>::type;
	using s4 = typename FilterArgsRec<s3>::type;
	using s5 = typename FilterPlusRec<s4>::type;
	using s6 = typename FilterMultRec<s5>::type;
	using type = s6;
};



#endif //_SIMPLIFY_H_

