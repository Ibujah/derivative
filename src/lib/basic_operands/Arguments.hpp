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

#include <meta/Operations.hpp>
#include <meta/Leaf.hpp>
#include <string>
#include "Integers.hpp"

/**
 * @brief Class representing the n-th input argument of a function
 */
template<unsigned int n>
class LeafArgument
{
    public:
		/**
		 * @brief Recursive evaluation of the n-th argument of the function
		 */
        template<typename ...Args>
        static inline double eval(const double &, Args... args)
        {
            return LeafArgument<n-1>::eval(args...);
        };

		/**
		 * @brief Recursive evaluation of the n-th argument of the function
		 */
        template<typename T, typename ...Args>
        static inline double eval(const T &, Args... args)
        {
            return eval(args...);
        };

		/**
		 * @brief Recursive writing of the n-th argument of the function
		 */
        template<typename ...Args>
        static std::string write(Args... )
        {
            return "x" + std::to_string(n);
        };
};

template<>
class LeafArgument<0>
{
    public:
        template<typename ...Args>
        static inline double eval(const double &x, Args...)
        {
            return x;
        };

        template<typename T, typename ...Args>
        static inline double eval(const T &, Args... args)
        {
            return eval(args...);
        };

        template<typename ...Args>
        static std::string write(Args...)
        {
            return "x0";
        };
};

/**
 * @brief Class representing an argument as a leaf
 */
template<unsigned int n>
using Argument = Leaf<LeafArgument<n> >;

/**
 * @brief Derivative of the argument with respect to an argument
 */
template<unsigned int n>
struct Der<Argument<n>,Argument<n> >
{
    using type = One;
};

template<unsigned int n, unsigned int m>
struct Der<Argument<n>,Argument<m> >
{
    using type = Zero;
};



using X = Argument<0>;
using Y = Argument<1>;
using Z = Argument<2>;

#endif //_ARGUMENTS_H_
