#ifndef _PLUS_H_
#define _PLUS_H_

#include <differential/Derivative.hpp>
#include <basic_operands/Integers.hpp>
#include "List_Op_Comm.hpp"

class OpPlus
{
	public:
		static inline double operation(double arg1, double arg2)
		{
			return arg1 + arg2;	
		};


		template<typename O1, typename O2>
		struct OpInt
		{};

		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1>,Integer<n2> >
		{
			using type = Integer<n1+n2>;
		};
		
		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1,false>,Integer<n2,false> >
		{
			using type = Integer<n1+n2,false>;
		};
		
		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1,true>,Integer<n2,false> >
		{
			using type = typename std::conditional<
							n1 >= n2,
							Integer<n1 - n2>,
							Integer<n2 - n1,false> >;
		};
		
		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1,false>,Integer<n2,true> >
		{
			using type = typename OpInt<Integer<n2,true>,Integer<n1,false> >::type;
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