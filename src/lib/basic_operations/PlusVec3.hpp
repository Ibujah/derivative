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

#ifndef _PLUSVEC3_H_
#define _PLUSVEC3_H_

#include <meta_operations/MetaOperations.hpp>
#include <basic_operands/Vector3.hpp>
#include "List_Op_Comm.hpp"
#include "Plus.hpp"

class OpPlusVec3
{
	public:
		static inline Eigen::Vector3d operation(const Eigen::Vector3d& arg1, const Eigen::Vector3d& arg2)
		{
			return arg1 + arg2;	
		};
		
		static constexpr char symb = '+';
		
		template<typename T1, typename T2>
		struct OpVec {};
		
		template<typename XV1, typename YV1, typename ZV1, typename XV2, typename YV2, typename ZV2>
		struct OpVec<Vector3<XV1,YV1,ZV1>,Vector3<XV2,YV2,ZV2> >
		{
			using type = Vector3<Plus<XV1,XV2>,Plus<YV1,YV2>,Plus<ZV1,ZV2> >;
		};
};

template<typename O1, typename... Ops>
using PlusVec3 = List_Op_Comm<OpPlusVec3,O1,Ops...>;

template<>
struct Neutral<OpPlusVec3>
{
	using type = Vector3<Zero,Zero,Zero>;
};

template<typename O1, typename A, typename... Ops>
struct Der<PlusVec3<O1,Ops...>, A>
{
	using DerO1 = typename Der<O1,A>::type;
    using type = PlusVec3<DerO1>;
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<PlusVec3<O1,O2,Ops...>, A>
{
	using DerO1 = typename Der<O1,A>::type;
	using next  = typename Der<PlusVec3<O2,Ops...>,A>::type;
    using type  = typename PlusVec3<DerO1>::template append<next>::type;
};

#endif //_PLUSVEC3_H_
