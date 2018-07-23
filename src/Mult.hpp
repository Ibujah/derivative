#ifndef _MULT_H_
#define _MULT_H_

#include "Derivative.hpp"
#include "Plus.hpp"

template<typename O1, typename O2, typename... Ops>
class Mult
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...)*O2::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return O1::write(args...) + "." + O2::write(args...);
        }
};

template<typename O1, typename O2, typename O3, typename... Ops>
class Mult<O1,O2,O3,Ops...>
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...)*Mult<O2,O3,Ops...>::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return O1::write(args...) + "." + Mult<O2,O3,Ops...>::write(args...);
        }
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<Mult<O1,O2,Ops...>, A>
{
    using der = Plus< Mult<typename Der<O1,A>::der,O2>, Mult<O1,typename Der<O2,A>::der> >;
};

template<typename O1, typename O2, typename O3, typename A, typename... Ops>
struct Der<Mult<O1,O2,O3,Ops...>, A>
{
    using der = Plus< Mult<typename Der<O1,A>::der,O2,O3,Ops...>,
					  Mult<O1,typename Der<Mult<O2,O3,Ops...>,A>::der> >;
};

#endif //_MULT_H_
