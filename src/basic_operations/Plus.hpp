#ifndef _PLUS_H_
#define _PLUS_H_

#include "../differential/Derivative.hpp"
#include "../basic_operands/Integers.hpp"
#include "List_Op_Comm.hpp"

class OpPlus
{
	public:
		static inline double operation(double arg1, double arg2)
		{
			return arg1 + arg2;	
		};
};

template<typename O1, typename... Ops>
using Plus = List_Op_Comm<OpPlus,'+',O1,Ops...>;

template<>
struct Neutral<OpPlus>
{
	using type = Zero;
};

template<typename O1, typename A, typename... Ops>
struct Der<Plus<O1,Ops...>, A>
{
    using type = Plus<typename Der<O1,A>::type>;
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<Plus<O1,O2,Ops...>, A>
{
    using type = Plus<typename Der<O1,A>::type,typename Der<Plus<O2,Ops...>,A>::type>;
};

#endif //_PLUS_H_
