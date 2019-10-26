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

#include <meta/Operations.hpp>
#include <meta/Leaf.hpp>
#include <string>

/**
 * @brief Class representing a positive or negative integer
 * @param n  Absolute value of the integer
 * @param p  True: positive, False: negative
 */
template<unsigned int n, bool p>
class LeafInteger
{
    public:
		/**
		 * @brief Evaluation of the integer value
		 */
        template<typename ...Args>
        static inline double eval(Args...)
        {
			return (p?1.0:-1.0)*(double)n;
        };

		/**
		 * @brief Writing of the integer value
		 */
        template<typename ...Args>
        static std::string write(Args...)
        {
			return (p?"":"-") + std::to_string(n);
        };
};

/**
 * @brief Class representing an integer as a leaf
 */
template<unsigned int n, bool p>
using Integer = Leaf<LeafInteger<n,p> >;

/**
 * @brief Class representing a shorter way to declare a positive integer
 */
template<unsigned int n>
using Positive = Integer<n,true>;

/**
 * @brief Class representing a shorter way to declare a negative integer
 */
template<unsigned int n>
using Negative = Integer<n,false>;

/**
 * @brief Derivative of the integer with respect to an argument
 */
template<unsigned int n, bool p, typename A>
struct Der<Integer<n,p>,A>
{
    using type = Integer<0,true>;
};

using Zero = Positive<0>;
using One = Positive<1>;


#endif //_INTEGERS_H_
