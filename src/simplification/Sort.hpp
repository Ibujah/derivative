#ifndef _SORT_H_
#define _SORT_H_

#include "../basic_operands/Integers.hpp"
#include "../basic_operations/List_Op_Comm.hpp"
#include <type_traits>

// defining order relations
template<typename O1, typename O2> // inferior or equals
struct Order {
	static const bool value = std::true_type::value;
	using lower = O1;
	using higher = O2;
};

// Integer
template<unsigned int n, typename O>
struct Order<O,Integer<n> > {
	static const bool value = std::false_type::value;
	using lower = Integer<n>;
	using higher = O;
};

template<unsigned int n, unsigned int na>
struct Order<Integer<n>,Argument<na> > {
	static const bool value = std::true_type::value;
	using lower = Integer<n>;
	using higher = Argument<na>;
};


// arguments
template<unsigned int n1, unsigned int n2>
struct Order<Argument<n1>,Argument<n2> > {
	static const bool value = n1 <= n2;
	using lower  = Argument<n1<=n2?n1:n2>;
	using higher = Argument<n1<=n2?n2:n1>;
};

template<unsigned int n, typename O>
struct Order<O,Argument<n> > {
	static const bool value = std::false_type::value;
	using lower = Argument<n>;
	using higher = O;
};



template<typename O1, typename O2>
struct Separate
{};

template<typename OpCom, char symb, typename O1, typename O2, typename... Args>
struct Separate<O1,List_Op_Comm<OpCom,symb,O2,Args...> >
{
	using inf = typename std::conditional
				<Order<O1,O2>::value,
				void,
				List_Op_Comm<OpCom,symb,O2> >::type;
	using sup = typename std::conditional
				<Order<O1,O2>::value,
				List_Op_Comm<OpCom,symb,O2>,
				void>::type;
};

template<typename OpCom, char symb, typename O1, typename O2, typename O3, typename... Args>
struct Separate<O1,List_Op_Comm<OpCom,symb,O2,O3,Args...> >
{
	using infnext = typename Separate<O1,List_Op_Comm<OpCom,symb,O3,Args...> >::inf;
	using supnext = typename Separate<O1,List_Op_Comm<OpCom,symb,O3,Args...> >::sup;
	
	using inf = typename std::conditional
				<Order<O1,O2>::value,
				infnext,
				typename std::conditional
					<std::is_same<infnext,void>::value,
					List_Op_Comm<OpCom,symb,O2>,
					typename List_Op_Comm<OpCom,symb,O2>::template append<infnext>::type >::type >::type;

	using sup = typename std::conditional
				<Order<O1,O2>::value,
				typename std::conditional
					<std::is_same<supnext,void>::value,
					List_Op_Comm<OpCom,symb,O2>,
					typename List_Op_Comm<OpCom,symb,O2>::template append<supnext>::type >::type,
				supnext>::type;
};



template<typename F>
struct Sort {
	using type = F;
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Args>
struct Sort<List_Op_Comm<OpCom,symb,O1,O2,Args...> >
{
	using pivot = O1;
	using inf = typename Sort<typename Separate<O1,List_Op_Comm<OpCom,symb,O2,Args...> >::inf>::type;
	using sup = typename Sort<typename Separate<O1,List_Op_Comm<OpCom,symb,O2,Args...> >::sup>::type;

	using inter = typename std::conditional
					<std::is_same<sup,void>::value,
					List_Op_Comm<OpCom,symb,pivot>,
					typename List_Op_Comm<OpCom,symb,pivot>::template append<sup>::type >::type;
	
	using type  = typename std::conditional
					<std::is_same<inf,void>::value,
					inter,
					typename inter::template rev_append<inf>::type >::type;
};

template<typename O>
struct SortRec
{
	using type = typename Sort<typename O::template apply_rec<Sort>::type>::type;
};

#endif //_SORT_H_
