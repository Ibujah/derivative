#ifndef _INVERSE_H_
#define _INVERSE_H_

#include <differential/Derivative.hpp>
#include <basic_operands/Integers.hpp>
#include "Mult.hpp"

template<typename O>
class Inverse
{
	public:
        template<typename ...Args>
		static inline double eval(Args... args)
		{
			return 1.0/O::eval(args...);
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(1/" + O::write(args...) + ")";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = Inverse<typename F<typename O::template apply_rec<F>::type>::type>;
		};
};

template<typename O, typename A>
struct Der<Inverse<O>, A>
{
	using type = Mult<Negative<1>,typename Der<O,A>::type,Inverse<Mult<O,O> > >;
};

#endif //_INVERSE_H_
