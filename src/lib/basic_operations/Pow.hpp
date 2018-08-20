#ifndef _POW_H_
#define _POW_H_

#include <differential/Derivative.hpp>
#include <basic_operands/Integers.hpp>
#include "Mult.hpp"
#include "Plus.hpp"
#include "Ln.hpp"

template<typename O1, typename O2>
class Pow
{
	public:
        template<typename ...Args>
		static inline double eval(Args... args)
		{
			return pow(O1::eval(args...),O2::eval(args...));
		};
		
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + "^" + O2::write(args...) + ")";
        };
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = Pow<typename F<typename O1::template apply_rec<F>::type>::type,typename F<typename O2::template apply_rec<F>::type>::type>;
		};
};

template<typename O1, typename O2, typename A>
struct Der<Pow<O1,O2>, A>
{
	using type = 
		Mult<   Pow<O1,Plus<O2,Integer<1,false> > >,
				Plus<
					Mult<O2,typename Der<O1,A>::type>,
					Mult<O1,Ln<O1>,typename Der<O2,A>::type>
					>
			>;
};

#endif //_POW_H_

