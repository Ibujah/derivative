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

#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

#include <differential/Derivative.hpp>
#include "Integers.hpp"

template<unsigned int n>
class Argument
{
    public:
        template<typename T, typename ...Args>
        static inline double eval(const T &p, Args... args)
        {
            return Argument<n>::eval(args...);
        };
        template<typename ...Args>
        static inline double eval(const double &x, Args... args)
        {
            return Argument<n-1>::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "x" + std::to_string(n);
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = typename F<Argument<n> >::type;
		};
};

template<>
class Argument<0>
{
    public:
        template<typename T, typename ...Args>
        static inline double eval(const T &p, Args... args)
        {
            return Argument<0>::eval(args...);
        };
        template<typename ...Args>
        static inline double eval(const double &x, Args... args)
        {
            return x;
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "x0";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = typename F<Argument<0> >::type;
		};
};

template<unsigned int n>
struct Der<Argument<n>,Argument<n> >
{
    using type = One;
};

template<unsigned int n, unsigned int nA>
struct Der<Argument<n>,Argument<nA> >
{
    using type = Zero;
};

using X = Argument<0>;
using Y = Argument<1>;
using Z = Argument<2>;

#endif //_ARGUMENTS_H_
