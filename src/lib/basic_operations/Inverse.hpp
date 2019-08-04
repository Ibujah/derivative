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

#ifndef _INVERSE_H_
#define _INVERSE_H_

#include <meta_operations/MetaOperations.hpp>
#include <basic_operands/Integers.hpp>
#include "Mult.hpp"

template<typename O>
class Inverse
{
	public:
        template<typename ...Args>
		static inline double eval(Args... args)
		{
			return 1.0/O::eval(args...);
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(1/" + O::write(args...) + ")";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = Inverse<typename F<typename O::template apply_rec<F>::type>::type>;
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

template<typename O, typename A>
struct Der<Inverse<O>, A>
{
	using type = Mult<Negative<1>,typename Der<O,A>::type,Inverse<Mult<O,O> > >;
};

#endif //_INVERSE_H_
