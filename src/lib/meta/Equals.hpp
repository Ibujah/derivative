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

#ifndef _EQUALS_H_
#define _EQUALS_H_

#include <graph/Leaf.hpp>
#include <graph/Node.hpp>

/**
 * @brief Comparison between A and B
 */
template<typename A, typename B>
struct Equals{};

//Leaves
template<typename A>
struct Equals<Leaf<A>,Leaf<A> >{
	const static bool value = true;	
};

template<typename A, typename B>
struct Equals<Leaf<A>,Leaf<B> >{
	const static bool value = false;	
};

//Nodes
template<typename Op, typename A>
struct Equals<Node<Op,A>,Node<Op,A> >{
	const static bool value = true;	
};

template<typename Op, typename A, typename B>
struct Equals<Node<Op,A>,Node<Op,B> >{
	const static bool value = Equals<A,B>::value;	
};

template<typename Op1, typename Op2, typename A, typename B>
struct Equals<Node<Op1,A>,Node<Op2,B> >{
	const static bool value = false;	
};

#endif //_EQUALS_H_
