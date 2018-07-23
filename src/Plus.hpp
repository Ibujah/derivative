#ifndef _PLUS_H_
#define _PLUS_H_

#include "Derivative.hpp"

template<typename O1, typename O2, typename... Ops>
class Plus
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...)+O2::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + "+" + O2::write(args...) + ")";
        }
};

template<typename O1, typename O2, typename O3, typename... Ops>
class Plus<O1,O2,O3,Ops...>
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...)+Plus<O2,O3,Ops...>::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + "+" + Plus<O2,O3,Ops...>::write(args...) + ")";
        }
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<Plus<O1,O2,Ops...>, A>
{
    using value = Plus<typename Der<O1,A>::value,typename Der<O2,A>::value>;
};

template<typename O1, typename O2, typename O3, typename A, typename... Ops>
struct Der<Plus<O1,O2,O3,Ops...>, A>
{
    using value = Plus<typename Der<O1,A>::value,typename Der<Plus<O2,O3,Ops...>,A>::value>;
};

#endif //_PLUS_H_
