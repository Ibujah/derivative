#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include "../basic_operands/Integers.hpp"
#include "../basic_operations/List_Op_Comm.hpp"

template<typename F>
struct Simp {
	using type = F;
};

template<typename OpCom, char symb, unsigned int n1, unsigned int n2, bool b1, bool b2>
struct Simp<List_Op_Comm<OpCom,symb,Integer<n1,b1>,Integer<n2,b2> > >
{
	using type = typename OpCom::template OpInt<Integer<n1,b1>,Integer<n2,b2> >::type;
};

template<typename OpCom, char symb, unsigned int n1, unsigned int n2, bool b1, bool b2, typename O, typename... Args>
struct Simp<List_Op_Comm<OpCom,symb,Integer<n1,b1>,Integer<n2,b2>,O,Args...> >
{
	using type = typename Simp<List_Op_Comm<OpCom,symb,typename OpCom::template OpInt<Integer<n1,b1>,Integer<n2,b2> >::type,O,Args...> >::type;
};

template<typename O>
struct SimpRec
{
	using type = typename Simp<typename O::template apply_rec<Simp>::type>::type;
};


#endif //_SIMPLIFY_H_

