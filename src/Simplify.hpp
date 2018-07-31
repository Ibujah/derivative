#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include "Integers.hpp"
#include "Plus.hpp"
#include "Mult.hpp"

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



/*template<unsigned int n1, unsigned int n2>
struct Order<Integer<n1>, Integer<n2> > {
	using value = std::true_type;
};

template<unsigned int n, typename O>
struct Order<Integer<n>, O> {
	using value = std::true_type;
};*/

template<typename O1, typename O2>
struct Separate
{};

template<typename O1, typename O2, typename... Args>
struct Separate<O1,Plus<O2,Args...> >
{
	using inf = typename std::conditional
				<Order<O1,O2>::value,
				void,
				Plus<O2> >::type;
	using sup = typename std::conditional
				<Order<O1,O2>::value,
				Plus<O2>,
				void>::type;
};

template<typename O1, typename O2, typename O3, typename... Args>
struct Separate<O1,Plus<O2,O3,Args...> >
{
	using infnext = typename Separate<O1,Plus<O3,Args...> >::inf;
	using supnext = typename Separate<O1,Plus<O3,Args...> >::sup;
	
	using inf = typename std::conditional
				<Order<O1,O2>::value,
				infnext,
				typename std::conditional
					<std::is_same<infnext,void>::value,
					Plus<O2>,
					typename Plus<O2>::template append<infnext>::type >::type >::type;

	using sup = typename std::conditional
				<Order<O1,O2>::value,
				typename std::conditional
					<std::is_same<supnext,void>::value,
					Plus<O2>,
					typename Plus<O2>::template append<supnext>::type >::type,
				supnext>::type;
};


template<typename F>
struct Sort {
	using type = F;
};

template<typename O>
struct Sort<Plus<O> >
{
	using type = Plus<O>;
};

template<typename O1, typename O2, typename... Args>
struct Sort<Plus<O1,O2,Args...> >
{
	using pivot = O1;
	using inf = typename Sort<typename Separate<O1,Plus<O2,Args...> >::inf>::type;
	using sup = typename Sort<typename Separate<O1,Plus<O2,Args...> >::sup>::type;

	using inter = typename std::conditional
					<std::is_same<sup,void>::value,
					Plus<pivot>,
					typename Plus<pivot>::template append<sup>::type >::type;
	
	using type  = typename std::conditional
					<std::is_same<inf,void>::value,
					inter,
					typename inf::template append<inter>::type >::type;
};

template<typename F>
struct Simp {
	using type = F;
};

template<unsigned int n1, unsigned int n2, typename... Args>
struct Simp<Plus<Integer<n1>,Integer<n2>,Args...> >
{
	using type = Integer<n1+n2>;
};

template<unsigned int n1, unsigned int n2, typename O, typename... Args>
struct Simp<Plus<Integer<n1>,Integer<n2>,O,Args...> >
{
	using type = typename Simp<Plus<Integer<n1+n2>,O,Args...> >::type;
};


#endif //_SIMPLIFY_H_

