#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include "../basic_operands/Integers.hpp"
#include "../basic_operations/List_Op_Comm.hpp"


template<typename O>
struct RemOp
{
	using type = O;
};

template<typename OpCom, char symb, typename O1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,O1,Ops...> >
{
	using type = List_Op_Comm<OpCom,symb,O1>;
};

template<typename OpCom, char symb, typename O1, typename... Ops1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,List_Op_Comm<OpCom,symb,O1,Ops1...>,Ops...> >
{
	using type = typename RemOp<List_Op_Comm<OpCom,symb,O1,Ops1...> >::type;
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Ops1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,List_Op_Comm<OpCom,symb,O1,Ops1...>,O2,Ops...> >
{
	using next = typename RemOp<List_Op_Comm<OpCom,symb,O2,Ops...> >::type;
	using type = typename RemOp<List_Op_Comm<OpCom,symb,O1,Ops1...> >::type::template append<next>::type;
};

template<typename OpCom1, char symb1, typename OpCom2, char symb2, typename O1, typename O2, typename... Ops1, typename... Ops>
struct RemOp<List_Op_Comm<OpCom1,symb1,List_Op_Comm<OpCom2,symb2,O1,Ops1...>,O2,Ops...> >
{
	using next = typename RemOp<List_Op_Comm<OpCom1,symb1,O2,Ops...> >::type;
	using type = typename List_Op_Comm<OpCom1,symb1,typename RemOp<List_Op_Comm<OpCom2,symb2,O1,Ops1...> >::type>::template append<next>::type;
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Ops>
struct RemOp<List_Op_Comm<OpCom,symb,O1,O2,Ops...> >
{
	using next = typename RemOp<List_Op_Comm<OpCom,symb,O2,Ops...> >::type;
	using type = typename List_Op_Comm<OpCom,symb,O1>::template append<next>::type;
};






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

template<typename OpCom, char symb, typename O>
struct Sort<List_Op_Comm<OpCom,symb,O> >
{
	using type = List_Op_Comm<OpCom,symb,typename Sort<O>::type>;
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Args>
struct Sort<List_Op_Comm<OpCom,symb,O1,O2,Args...> >
{
	using pivot = typename Sort<O1>::type;
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




template<typename F>
struct Simp {
	using type = F;
};

template<typename OpCom, char symb, unsigned int n1, unsigned int n2, typename... Args>
struct Simp<List_Op_Comm<OpCom,symb,Integer<n1>,Integer<n2>,Args...> >
{
	using type = typename OpCom::template OpInt<n1,n2>;
};

template<typename OpCom, char symb, unsigned int n1, unsigned int n2, typename O, typename... Args>
struct Simp<List_Op_Comm<OpCom,symb,Integer<n1>,Integer<n2>,O,Args...> >
{
	using type = typename Simp<List_Op_Comm<OpCom,symb,typename OpCom::template OpInt<n1,n2>,O,Args...> >::type;
};

template<typename OpCom, char symb, unsigned int n, typename O, typename... Args>
struct Simp<List_Op_Comm<OpCom,symb,Integer<n>,O,Args...> >
{
	using type = typename List_Op_Comm<OpCom,symb,Integer<n> >::template append<typename Simp<List_Op_Comm<OpCom,symb,O,Args...> >::type >::type;
};

template<typename OpCom, char symb, typename O, typename... Args>
struct Simp<List_Op_Comm<OpCom,symb,O,Args...> >
{
	using type = List_Op_Comm<OpCom,symb,typename Simp<O>::type>;
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Args>
struct Simp<List_Op_Comm<OpCom,symb,O1,O2,Args...> >
{
	using type = typename List_Op_Comm<OpCom,symb,typename Simp<O1>::type>::template append<typename Simp<List_Op_Comm<OpCom,symb,O2,Args...> >::type >::type;
};


#endif //_SIMPLIFY_H_

