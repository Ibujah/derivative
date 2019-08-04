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

#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <meta_operations/MetaOperations.hpp>
#include "Arguments.hpp"

#include <sstream>

/**
 * @brief Class representing the n-th parameter of the function (because double can't be used as template value)
 */
template<unsigned int n>
class Parameter
{
    public:
		/**
		 * 0brief Value of the parameter
		 */
        double a;

		/**
		 * 0brief Next parameter
		 */
        Parameter<n-1> p;
        
    public:
		/**
		 * @brief Contructor
		 * @brief a_    Current value
		 * @brief args_ Next values
		 */
        template<typename ...Args>
        Parameter(const double &a_, Args... args) : a(a_), p(args...)
        {};
        
		/**
		 * @brief Evaluation of the parameter value
		 */
        template<unsigned int m, typename ...Args>
        static inline double eval(const Parameter<m> &p, Args... args)
        {
            return Parameter<n-1>::eval(p.p);
        };
        
		/**
		 * @brief Writing of the parameter value
		 */
        template<unsigned int m, typename ...Args>
        static std::string write(const Parameter<m> &p, Args... args)
        {
            return Parameter<n-1>::write(p.p);
        };

		/**
		 * @brief Struct recursively applying the modifier F<T>
		 */
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = typename F<Parameter<n> >::type;
		};

		/**
		 * @brief Importance order
		 */
		static const unsigned int outerOrder = 2;

		/**
		 * @brief Importance order
		 */
		static const unsigned int innerOrder = 0;
};

template<>
class Parameter<0>
{};

template<>
class Parameter<1>
{
    public:
        double a;
        
    public:
        Parameter(const double &a_) : a(a_)
        {};

        template<unsigned int m, typename ...Args>
        static inline double eval(const Parameter<m> &p, Args... args)
        {
            return p.a;
        };
        
        template<unsigned int m,typename ...Args>
        static std::string write(const Parameter<m> &p, Args... args)
        {
			std::stringstream ss;
			ss.precision(2);
			ss.setf(std::ios::fixed, std:: ios::floatfield);
			ss << p.a;
            return ss.str();
        };

		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = typename F<Parameter<1> >::type;
		};

		/**
		 * @brief Importance order
		 */
		static const unsigned int outerOrder = 2;

		/**
		 * @brief Importance order
		 */
		static const unsigned int innerOrder = 0;
};

/**
 * @brief Function of build quickly a set of parameters
 */
Parameter<1> param(const double &x)
{
    return Parameter<1>(x);
}

/**
 * @brief Function of build quickly a set of parameters
 */
template<unsigned int n, typename ...Args>
Parameter<n> param(const double &x, Args... args)
{
    return Parameter<n>(x,Parameter<n-1>(args...));
}

using A1 = Parameter<1>;
using A2 = Parameter<2>;
using A3 = Parameter<3>;

/**
 * @brief Derivative of the parameter with respect to an argument
 */
template<unsigned int n, typename A>
struct Der<Parameter<n>,A>
{
    using type = Zero;
};

#endif //_PARAMETERS_H_
