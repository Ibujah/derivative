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

#ifndef _DOTVEC3_H_
#define _DOTVEC3_H_

#include <meta_operations/MetaOperations.hpp>
#include <basic_operands/Vector3.hpp>
#include "Plus.hpp"

template<typename O1, typename O2>
class DotVec3
{
	public:
        template<typename ...Args>
		static inline double eval(Args... args)
		{
			const Eigen::Vector3d& vec1 = O1::eval(args...);
			const Eigen::Vector3d& vec2 = O2::eval(args...);
			return vec1.dot(vec2);
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "<" + O1::write() + "," + O2::write() + ">";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = DotVec3<
				typename F<typename O1::template apply_rec<F>::type>::type,
				typename F<typename O2::template apply_rec<F>::type>::type >;
		};

		/**
		 * @brief Importance order
		 */
		static const unsigned int outerOrder = 3;

		/**
		 * @brief Importance order
		 */
		static const unsigned int innerOrder = 0;
};

template<typename O1, typename O2, typename A>
struct Der<DotVec3<O1,O2>, A>
{
	using DerO1 = typename Der<O1,A>::type;
	using DerO2 = typename Der<O2,A>::type;
    using type = Plus<DotVec3<DerO1,O2>, DotVec3<O1,DerO2> >;
};

#endif //_DOTVEC3_H_
