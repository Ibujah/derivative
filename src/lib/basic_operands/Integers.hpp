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

#ifndef _INTEGERS_H_
#define _INTEGERS_H_

#include <differential/Derivative.hpp>

template<unsigned int n, bool b = true>
class Integer
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
			return (b?1.0:-1.0)*(double)n;
        };

        template<typename ...Args>
        static std::string write(Args... args)
        {
			return (b?"":"-") + std::to_string(n);
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = typename F<Integer<n> >::type;
		};
};

template<unsigned int n>
using Negative = Integer<n,false>;

template<unsigned int n, bool b,typename A>
struct Der<Integer<n,b>,A>
{
    using type = Integer<0>;
};

using Zero = Integer<0>;
using One = Integer<1>;


#endif //_INTEGERS_H_
