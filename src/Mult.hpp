#ifndef _MULT_H_
#define _MULT_H_

#include "Derivative.hpp"
#include "Plus.hpp"

template<typename O1, typename... Ops>
class Mult
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...);
        };

    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return O1::write(args...);
        }
};

template<typename O1, typename O2, typename... Ops>
class Mult<O1,O2,Ops...> : public Mult<O2,Ops...>
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...) + "+" + Mult<O2,Ops...>::write_int(args...);
        };

    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...)*Mult<O2,Ops...>::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + "*" + Mult<O2,Ops...>::write_int(args...) + ")";
        }
};


template<typename O1, typename A, typename... Ops>
struct Der<Mult<O1,Ops...>, A>
{
    using type = typename Der<O1,A>::type;
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<Mult<O1,O2,Ops...>, A>
{
    using type = Plus< Mult<typename Der<O1,A>::type,O2,Ops...>,
						Mult<O1,typename Der<Mult<O2,Ops...>,A>::type> >;
};

#endif //_MULT_H_
