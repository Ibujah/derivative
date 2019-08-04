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

#ifndef _MULTVEC2_H_
#define _MULTVEC2_H_

#include <meta_operations/MetaOperations.hpp>
#include <basic_operands/Vector2.hpp>
#include "PlusVec2.hpp"

template<typename O1, typename O2>
class MultVec2
{
	public:
        template<typename ...Args>
		static inline Eigen::Vector2d eval(Args... args)
		{
			const double& scal = O1::eval(args...);
			const Eigen::Vector2d& vec = O2::eval(args...);
			return scal*vec;
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return O1::write() + "*" + O2::write();
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = MultVec2<
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
struct Der<MultVec2<O1,O2>, A>
{
    using type = PlusVec2<MultVec2<typename Der<O1,A>::type,O2>,MultVec2<O1,typename Der<O2,A>::type> >;
};

#endif //_MULTVEC2_H_
