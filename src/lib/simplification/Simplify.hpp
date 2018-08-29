/*
MIT License

Copyright (c) 2018 Bastien Durix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include <basic_operands/Integers.hpp>
#include <basic_operands/Arguments.hpp>
#include <basic_operations/List_Op_Comm.hpp>
#include "Sort.hpp"
#include "RemoveOp.hpp"

/*template<typename F>
struct FilterInt {
	using type = F;
};

template<typename OpCom, unsigned int n1, unsigned int n2, bool b1, bool b2>
struct FilterInt<List_Op_Comm<OpCom,Integer<n1,b1>,Integer<n2,b2> > >
{
	using type = typename OpCom::template OpInt<Integer<n1,b1>,Integer<n2,b2> >::type;
};

template<typename OpCom, unsigned int n1, unsigned int n2, bool b1, bool b2, typename O, typename... Ops>
struct FilterInt<List_Op_Comm<OpCom,Integer<n1,b1>,Integer<n2,b2>,O,Ops...> >
{
	using type = typename FilterInt<List_Op_Comm<OpCom,typename OpCom::template OpInt<Integer<n1,b1>,Integer<n2,b2> >::type,O,Ops...> >::type;
};

template<typename O>
struct FilterIntRec
{
	using type = typename FilterInt<typename O::template apply_rec<FilterInt>::type>::type;
};*/

template<typename Filt, typename F>
struct FilterList {
	using type = F;
};

template<typename Filt, typename OpCom, typename A, typename B>
struct FilterList<Filt,List_Op_Comm<OpCom,A,B> > {
	static const bool valA = Filt::template is_valid<A>::value;
	static const bool valB = Filt::template is_valid<B>::value;
	using type = typename std::conditional<
		valA && valB,
		List_Op_Comm<OpCom,typename Filt::template comb<A,B>::type>,
		List_Op_Comm<OpCom,A,B>
		>::type;
};

template<typename Filt, typename OpCom, typename A, typename B, typename C, typename... Ops>
struct FilterList<Filt,List_Op_Comm<OpCom,A,B,C,Ops...> > {
	static const bool valA = Filt::template is_valid<A>::value;
	static const bool valB = Filt::template is_valid<B>::value;

	using notand = typename std::conditional<
		valA,
		typename FilterList<Filt,List_Op_Comm<OpCom,A,C,Ops...> >::type::template rev_append<B>::type,
		typename FilterList<Filt,List_Op_Comm<OpCom,B,C,Ops...> >::type::template rev_append<A>::type
		>::type;

	using type = typename std::conditional<
		valA && valB,
		typename FilterList<Filt,List_Op_Comm<OpCom,typename Filt::template comb<A,B>::type,C,Ops...> >::type,
		notand
		>::type;
};


template<typename OpCom>
struct FiltInt
{
	template<typename A>
	struct is_valid
	{
		static const bool value = false;
	};

	template<unsigned int n, bool b>
	struct is_valid<Integer<n,b> >
	{
		static const bool value = true;
	};
	
	template<typename A, typename B>
	struct comb
	{
		using type = void;
	};

	template<unsigned int n1, bool b1, unsigned int n2, bool b2>
	struct comb<Integer<n1,b1>,Integer<n2,b2> >
	{
		using type = typename OpCom::template OpInt<Integer<n1,b1>,Integer<n2,b2> >::type;
	};
};

template<typename O>
using FilterInt = FilterList<FiltInt<typename O::opcom>,O>;

template<typename O>
struct FilterIntRec
{
	using type = typename FilterInt<typename O::template apply_rec<FilterInt>::type>::type;
};


template<typename F>
struct FilterArgs {
	using type = F;
};

template<typename OpCom, unsigned int n, bool b, typename O, typename... Ops>
struct FilterArgs<List_Op_Comm<OpCom,Integer<n,b>,O,Ops... > >
{
	using next = typename FilterArgs<List_Op_Comm<OpCom,O,Ops... > >::type;
	using type = typename List_Op_Comm<OpCom,Integer<n,b> >::template append<next>::type;
};

template<unsigned int n, typename... Ops>
struct FilterArgs<List_Op_Comm<OpPlus,Argument<n>,Argument<n>,Ops... > >
{
	using type = typename FilterArgs<List_Op_Comm<OpPlus,Mult<Integer<2>,Argument<n> >,Ops... > >::type;
};

template<unsigned int n1, unsigned int n, typename... Ops>
struct FilterArgs<List_Op_Comm<OpPlus,Mult<Integer<n1>,Argument<n> >,Argument<n>,Ops... > >
{
	using type = typename FilterArgs<List_Op_Comm<OpPlus,Mult<Integer<n1+1>,Argument<n> >,Ops... > >::type;
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

