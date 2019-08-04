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

#ifndef _EXPAND_H_
#define _EXPAND_H_

#include <basic_operations/List_Op_Comm.hpp>
#include <basic_operations/DotVec2.hpp>
#include <basic_operations/PlusVec2.hpp>
#include <basic_operations/MultVec2.hpp>
#include <basic_operations/DotVec3.hpp>
#include <basic_operations/PlusVec3.hpp>
#include <basic_operations/MultVec3.hpp>
#include <basic_operations/Mult.hpp>
#include <basic_operations/Plus.hpp>

template<typename F>
struct FilterExpand1 {
	using type = F;
};

template<typename O1, typename O2, typename O3>
struct FilterExpand1<DotVec2<MultVec2<O1,O2>,O3> >
{
	using type  = Mult<O1,DotVec2<O2,O3> >;
};

template<typename O1, typename O2, typename... Ops>
struct FilterExpand1<DotVec2<PlusVec2<O1,Ops...>,O2> >
{
	using type = typename FilterExpand1<DotVec2<O1,O2> >::type;
};

template<typename O1, typename O2, typename O3, typename... Ops>
struct FilterExpand1<DotVec2<PlusVec2<O1,O2,Ops...>,O3> >
{
	using first = typename FilterExpand1<DotVec2<O1,O3> >::type;
	using next  = typename FilterExpand1<DotVec2< PlusVec2<O2,Ops...>,O3 > >::type;
	using type  = typename Plus<first>::template append<next>::type;
};

template<typename O>
struct FilterExpand1Rec
{
	using type = typename FilterExpand1<typename O::template apply_rec<FilterExpand1>::type>::type;
};



template<typename F>
struct FilterExpand2 {
	using type = F;
};

template<typename O1, typename O2, typename O3>
struct FilterExpand2<DotVec2<O1,MultVec2<O2,O3> > >
{
	using type  = Mult<O2,DotVec2<O1,O3> >;
};

template<typename O1, typename O2, typename... Ops>
struct FilterExpand2<DotVec2<O1,PlusVec2<O2,Ops...> > >
{
	using type = typename FilterExpand2<DotVec2<O1,O2> >::type;
};

template<typename O1, typename O2, typename O3, typename... Ops>
struct FilterExpand2<DotVec2<O1,PlusVec2<O2,O3,Ops...>> >
{
	using first = typename FilterExpand2<DotVec2<O1,O2> >::type;
	using next  = typename FilterExpand2<DotVec2< O1,PlusVec2<O3,Ops...> > >::type;
	using type  = typename Plus<first>::template append<next>::type;
};

template<typename O>
struct FilterExpand2Rec
{
	using type = typename FilterExpand2<typename O::template apply_rec<FilterExpand2>::type>::type;
};



template<typename F>
struct Expand {
	using e1 = typename FilterExpand1Rec<F>::type;
	using type = typename FilterExpand2Rec<e1>::type;
};


#endif //_EXPAND_H_
