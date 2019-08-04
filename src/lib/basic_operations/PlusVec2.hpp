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

#ifndef _PLUSVEC2_H_
#define _PLUSVEC2_H_

#include <meta_operations/MetaOperations.hpp>
#include <basic_operands/Vector2.hpp>
#include "List_Op_Comm.hpp"
#include "Plus.hpp"

class OpPlusVec2
{
	public:
		static inline Eigen::Vector2d operation(const Eigen::Vector2d& arg1, const Eigen::Vector2d& arg2)
		{
			return arg1 + arg2;	
		};
		
		static constexpr char symb = '+';
		
		template<typename T1, typename T2>
		struct OpVec {};
		
		template<typename XV1, typename YV1, typename XV2, typename YV2>
		struct OpVec<Vector2<XV1,YV1>,Vector2<XV2,YV2> >
		{
			using type = Vector2<Plus<XV1,XV2>,Plus<YV1,YV2> >;
		};
};

template<typename O1, typename... Ops>
using PlusVec2 = List_Op_Comm<OpPlusVec2,O1,Ops...>;

template<>
struct Neutral<OpPlusVec2>
{
	using type = Vector2<Zero,Zero>;
};

template<typename O1, typename A, typename... Ops>
struct Der<PlusVec2<O1,Ops...>, A>
{
	using DerO1 = typename Der<O1,A>::type;
    using type = PlusVec2<DerO1>;
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<PlusVec2<O1,O2,Ops...>, A>
{
	using DerO1 = typename Der<O1,A>::type;
	using next  = typename Der<PlusVec2<O2,Ops...>,A>::type;
    using type  = typename PlusVec2<DerO1>::template append<next>::type;
};

#endif //_PLUSVEC2_H_
