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

#ifndef _REMOVOP_H_
#define _REMOVOP_H_

#include <basic_operations/List_Op_Comm.hpp>

template<typename O>
struct RemOp
{
	using type = O;
};

template<typename OpCom, typename O1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,O1,Ops...> >
{
	using type = List_Op_Comm<OpCom,O1,Ops...>;
};

template<typename OpCom, typename O1, typename... Ops1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,List_Op_Comm<OpCom,O1,Ops1...>,Ops...> >
{
	using type = typename RemOp<List_Op_Comm<OpCom,O1,Ops1...> >::type;
};

template<typename OpCom, typename O1, typename O2, typename... Ops1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,List_Op_Comm<OpCom,O1,Ops1...>,O2,Ops...> >
{
	using next = typename RemOp<List_Op_Comm<OpCom,O2,Ops...> >::type;
	using type = typename RemOp<List_Op_Comm<OpCom,O1,Ops1...> >::type::template append<next>::type;
};

template<typename OpCom, typename O1, typename O2, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,O1,O2,Ops...> >
{
	using next = typename RemOp<List_Op_Comm<OpCom,O2,Ops...> >::type;
	using type = typename List_Op_Comm<OpCom,O1>::template append<next>::type;
};

template<typename O>
struct RemOpRec
{
	using type = typename RemOp<typename O::template apply_rec<RemOp>::type>::type;
};

#endif //_REMOVEOP_H_
