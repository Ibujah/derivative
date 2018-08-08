#ifndef _INTEGERS_H_
#define _INTEGERS_H_

#include <differential/Derivative.hpp>

template<unsigned int n, bool b = true>
class Integer
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
			return (b?1.0:-1.0)*(double)n;
        };

        template<typename ...Args>
        static std::string write(Args... args)
        {
			return (b?"":"-") + std::to_string(n);
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = typename F<Integer<n> >::type;
		};
};

template<unsigned int n>
using Negative = Integer<n,false>;

template<unsigned int n,typename A>
struct Der<Integer<n>,A>
{
    using type = Integer<0>;
};

using Zero = Integer<0>;
using One = Integer<1>;


#endif //_INTEGERS_H_
