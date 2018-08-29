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
		
		static constexpr char symb = '+';


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
using Plus = List_Op_Comm<OpPlus,O1,Ops...>;

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
