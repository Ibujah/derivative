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

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <meta_operations/MetaOperations.hpp>
#include <Eigen/Dense>

/**
 * @brief Class representing a 2D vector
 */
template<typename X0, typename X1>
class Vector2
{
    public:
		/**
		 * @brief Evaluation of the vector value
		 */
        template<typename T, typename ...Args>
        static inline Eigen::Vector2d eval(const T &p, Args... args)
		{
			return Eigen::Vector2d(X0::eval(p,args...),X1::eval(p,args...));
		};

		/**
		 * @brief Writing of the vector value
		 */
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + X0::write(args...) + "," + X1::write(args...) + ")";
        };
		
		/**
		 * @brief Struct recursively applying the modifier F<T>
		 */
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = Vector2<typename X0::template apply_rec<F>::type,
								 typename X1::template apply_rec<F>::type>;
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

/**
 * @brief Derivative of the parameter with respect to an argument
 */
template<typename X0, typename X1, typename A>
struct Der<Vector2<X0,X1>,A>
{
    using type = Vector2<typename Der<X0,A>::type,typename Der<X1,A>::type>;
};

/**
 * @brief Simplification of the 2D vector
 */
template<typename X0, typename X1>
struct Simp<Vector2<X0,X1> >
{
    using type = Vector2<typename Simp<X0>::type,typename Simp<X1>::type>;
};

#endif //_VECTOR2_H_
