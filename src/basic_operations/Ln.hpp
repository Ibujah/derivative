#ifndef _LN_H_
#define _LN_H_

#include "../differential/Derivative.hpp"
#include "../basic_operands/Integers.hpp"
#include "Mult.hpp"
#include "Inverse.hpp"

template<typename O>
class Ln
{
	public:
        template<typename ...Args>
		static inline double eval(Args... args)
		{
			return log(O::eval(args));	
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "ln(" + O::write(args...) + ")";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = Ln<typename F<typename O::template apply_rec<F>::type>::type>;
		};
};

template<typename O, typename A>
struct Der<Ln<O>, A>
{
	using type = Mult<Der<O,A>::type,Inverse<O> >;
};

#endif //_LN_H_



