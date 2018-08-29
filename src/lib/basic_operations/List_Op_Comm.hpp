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

#ifndef _LIST_OP_COMM_H_
#define _LIST_OP_COMM_H_

template<typename OpCom, typename O1, typename... Ops>
class List_Op_Comm
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...);
        };

    public:
		using opcom = OpCom;


        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...);
        };

        template<typename ...Args>
        static std::string write(Args... args)
        {
            return O1::write(args...);
        };
		

		template<typename O>
		struct append
		{
			using type = List_Op_Comm<OpCom,O1,Ops...,O>;
		};
	
		template<typename... O>
		struct append<List_Op_Comm<OpCom,O...> >
		{
			using type = List_Op_Comm<OpCom,O1,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = List_Op_Comm<OpCom,O,O1,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<List_Op_Comm<OpCom,O...> >
		{
			using type = List_Op_Comm<OpCom,O...,O1,Ops...>;
		};
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using type = List_Op_Comm<OpCom,typename F<typename O1::template apply_rec<F>::type>::type>;
		};
};

template<typename OpCom, typename O1, typename O2, typename... Ops>
class List_Op_Comm<OpCom,O1,O2,Ops...> : public List_Op_Comm<OpCom,O2,Ops...>
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...) + OpCom::symb + List_Op_Comm<OpCom,O2,Ops...>::write_int(args...);
        };

    public:
		using opcom = OpCom;


        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return OpCom::operation(O1::eval(args...),List_Op_Comm<OpCom,O2,Ops...>::eval(args...));
        };

        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + OpCom::symb + List_Op_Comm<OpCom,O2,Ops...>::write_int(args...) + ")";
        }
		

		template<typename O>
		struct append
		{
			using type = List_Op_Comm<OpCom,O1,O2,Ops...,O>;
		};
	
		template<typename... O>
		struct append<List_Op_Comm<OpCom,O...> >
		{
			using type = List_Op_Comm<OpCom,O1,O2,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = List_Op_Comm<OpCom,O,O1,O2,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<List_Op_Comm<OpCom,O...> >
		{
			using type = List_Op_Comm<OpCom,O...,O1,O2,Ops...>;
		};
		
		template<template<typename T> typename F>
		struct apply_rec
		{
			using next = typename List_Op_Comm<OpCom,O2,Ops...>::template apply_rec<F>::type;
			using type = typename List_Op_Comm<OpCom,typename F<typename O1::template apply_rec<F>::type>::type>::template append<next>::type;
		};
};

template<typename OpCom>
struct Neutral
{};

#endif //_LIST_OP_COMM_H_

