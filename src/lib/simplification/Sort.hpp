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

#ifndef _SORT_H_
#define _SORT_H_

#include <basic_operations/List_Op_Comm.hpp>
#include <type_traits>

/**
 * @brief Class representing an order relation between functions, using their inner and outer orders
 */
template<typename O1, typename O2> // inferior or equals
struct Order
{
	static const unsigned int outerO1 = O1::outerOrder;
	static const unsigned int outerO2 = O2::outerOrder;

	static const unsigned int innerO1 = O1::innerOrder;
	static const unsigned int innerO2 = O2::innerOrder;
	
	/**
	 * @brief True iff O1 <= O2
	 */
	static const bool value = ((outerO1 == outerO2 && innerO1 <= innerO2) || (outerO1 < outerO2));
	
	/**
	 * @brief Lower between O1 and O2
	 */
	using lower = typename std::conditional<value,O1,O2>::type;

	/**
	 * @brief Higher between O1 and O2
	 */
	using higher = typename std::conditional<value,O2,O1>::type;
};

/**
 * @brief Partition of the List_Op_Comm L relatively to the pivot P (for quicksort algorithm)
 * @detail Return inf, the list of elements of L that are lower to P, and sup, the list of elements of L that are higher to P
 */
template<typename P, typename L>
struct Partition
{};

template<typename OpCom, typename P, typename O1, typename... Args>
struct Partition<P,List_Op_Comm<OpCom,O1,Args...> >
{
	using inf = typename std::conditional
				<Order<P,O1>::value,
				void,
				List_Op_Comm<OpCom,O1> >::type;
	using sup = typename std::conditional
				<Order<P,O1>::value,
				List_Op_Comm<OpCom,O1>,
				void>::type;
};

template<typename OpCom, typename P, typename O1, typename O2, typename... Args>
struct Partition<P,List_Op_Comm<OpCom,O1,O2,Args...> >
{
	/**
	 * @brief Elements lower to P
	 */
	using infNext = typename Partition<P,List_Op_Comm<OpCom,O2,Args...> >::inf;

	/**
	 * @brief Elements higher to P
	 */
	using supNext = typename Partition<P,List_Op_Comm<OpCom,O2,Args...> >::sup;
	
	using concatInfVoid    = List_Op_Comm<OpCom,O1>;
	using concatInfNonVoid = typename List_Op_Comm<OpCom,O1>::template append<infNext>::type;
	
	using concatInf = typename std::conditional
					  <std::is_same<infNext,void>::value,
					   concatInfVoid,
					   concatInfNonVoid>::type;

	using inf = typename std::conditional
				<Order<P,O1>::value,
				 infNext,
				 concatInf >::type;

	using concatSupVoid    = List_Op_Comm<OpCom,O1>;
	using concatSupNonVoid = typename List_Op_Comm<OpCom,O1>::template append<supNext>::type;
	
	using concatSup = typename std::conditional
					  <std::is_same<supNext,void>::value,
					   concatSupVoid,
					   concatSupNonVoid>::type;

	using sup = typename std::conditional
				<Order<P,O1>::value,
				 concatSup,
				 supNext  >::type;
};


/**
 * @brief Sort the list of elements using a quicksort
 */
template<typename F>
struct Sort {
	using type = F;
};

template<typename OpCom, typename O1, typename O2, typename... Args>
struct Sort<List_Op_Comm<OpCom,O1,O2,Args...> >
{
	using pivot = O1;
	using inf = typename Sort<typename Partition<pivot,List_Op_Comm<OpCom,O2,Args...> >::inf>::type;
	using sup = typename Sort<typename Partition<pivot,List_Op_Comm<OpCom,O2,Args...> >::sup>::type;

	using concatSupVoid    = List_Op_Comm<OpCom,O1>;
	using concatSupNonVoid = typename List_Op_Comm<OpCom,O1>::template append<sup>::type;

	using inter = typename std::conditional
					<std::is_same<sup,void>::value,
					 concatSupVoid,
					 concatSupNonVoid  >::type;

	using concatInfVoid    = inter;
	using concatInfNonVoid = typename inter::template rev_append<inf>::type;
	
	using type  = typename std::conditional
					<std::is_same<inf,void>::value,
					concatInfVoid,
					concatInfNonVoid  >::type;
};

template<typename O>
struct SortRec
{
	using type = typename Sort<typename O::template apply_rec<Sort>::type>::type;
};

#endif //_SORT_H_
