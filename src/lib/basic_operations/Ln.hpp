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

#ifndef _LN_H_
#define _LN_H_

#include <math.h>

#include <differential/Derivative.hpp>
#include <basic_operands/Integers.hpp>
#include "Mult.hpp"
#include "Inverse.hpp"

template<typename O>
class Ln
{
	public:
        template<typename ...Args>
		static inline double eval(Args... args)
		{
			return log(O::eval(args...));
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "ln(" + O::write(args...) + ")";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = Ln<typename F<typename O::template apply_rec<F>::type>::type>;
		};
};

template<typename O, typename A>
struct Der<Ln<O>, A>
{
	using type = Mult<typename Der<O,A>::type,Inverse<O> >;
};

#endif //_LN_H_



