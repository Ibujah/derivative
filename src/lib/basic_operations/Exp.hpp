#ifndef _EXP_H_
#define _EXP_H_

#include <differential/Derivative.hpp>
#include <basic_operands/Integers.hpp>
#include "Mult.hpp"
#include <math.h>

template<typename O>
class Exp
{
	public:
        template<typename ...Args>
		static inline double eval(Args... args)
		{
			return exp(O::eval(args...));	
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "exp(" + O::write(args...) + ")";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = Exp<typename F<typename O::template apply_rec<F>::type>::type>;
		};
};

template<typename O, typename A>
struct Der<Exp<O>, A>
{
	using type = Mult<typename Der<O,A>::type,Exp<O> >;
};

#endif //_EXP_H_


