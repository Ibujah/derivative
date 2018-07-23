#ifndef _SIMPLIFY_H_
#define _SIMPLIFY_H_

#include "Integers.hpp"
#include "Plus.hpp"
#include "Mult.hpp"

template<typename F>
struct Simp {
	using value = F;
};

template<unsigned int n1, unsigned int n2, typename... Args>
struct Simp<Plus<Integer<n1>,Integer<n2>,Args...> >
{
	using value = Integer<n1+n2>;
};

template<unsigned int n1, unsigned int n2, typename O, typename... Args>
struct Simp<Plus<Integer<n1>,Integer<n2>,O,Args...> >
{
	using value = typename Simp<Plus<Integer<n1+n2>,O,Args...> >::value;
};


#endif //_SIMPLIFY_H_

