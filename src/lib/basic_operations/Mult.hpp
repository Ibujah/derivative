#ifndef _MULT_H_
#define _MULT_H_

#include <differential/Derivative.hpp>
#include <basic_operands/Integers.hpp>
#include "Plus.hpp"

class OpMult
{
	public:
		static inline double operation(double arg1, double arg2)
		{
			return arg1 * arg2;	
		};
		
		static constexpr char symb = '*';
		
		
		template<typename O1, typename O2>
		struct OpInt
		{};

		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1>,Integer<n2> >
		{
			using type = Integer<n1*n2>;
		};
		
		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1,false>,Integer<n2,false> >
		{
			using type = Integer<n1*n2>;
		};
		
		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1,true>,Integer<n2,false> >
		{
			using type = Integer<n1*n2,false>;
		};
		
		template<unsigned int n1, unsigned int n2>
		struct OpInt<Integer<n1,false>,Integer<n2,true> >
		{
			using type = Integer<n1*n2,false>;
		};
};

template<typename O1, typename... Ops>
using Mult = List_Op_Comm<OpMult,O1,Ops...>;

template<>
struct Neutral<OpMult>
{
	using type = One;
};

template<typename O1, typename A, typename... Ops>
struct Der<Mult<O1,Ops...>, A>
{
    using type = typename Der<O1,A>::type;
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<Mult<O1,O2,Ops...>, A>
{
    using type = Plus< Mult<typename Der<O1,A>::type,O2,Ops...>,
						Mult<O1,typename Der<Mult<O2,Ops...>,A>::type> >;
};

#endif //_MULT_H_
