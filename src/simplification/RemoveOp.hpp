#ifndef _REMOVOP_H_
#define _REMOVOP_H_

#include "../basic_operations/List_Op_Comm.hpp"

template<typename O>
struct RemOp
{
	using type = O;
};

template<typename OpCom, char symb, typename O1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,O1,Ops...> >
{
	using type = List_Op_Comm<OpCom,symb,O1>;
};

template<typename OpCom, char symb, typename O1, typename... Ops1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,List_Op_Comm<OpCom,symb,O1,Ops1...>,Ops...> >
{
	using type = typename RemOp<List_Op_Comm<OpCom,symb,O1,Ops1...> >::type;
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Ops1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,List_Op_Comm<OpCom,symb,O1,Ops1...>,O2,Ops...> >
{
	using next = typename RemOp<List_Op_Comm<OpCom,symb,O2,Ops...> >::type;
	using type = typename RemOp<List_Op_Comm<OpCom,symb,O1,Ops1...> >::type::template append<next>::type;
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,O1,O2,Ops...> >
{
	using next = typename RemOp<List_Op_Comm<OpCom,symb,O2,Ops...> >::type;
	using type = typename List_Op_Comm<OpCom,symb,O1>::template append<next>::type;
};

template<typename O>
struct RemOpRec
{
	using type = typename RemOp<typename O::template apply_rec<RemOp>::type>::type;
};

#endif //_REMOVEOP_H_
