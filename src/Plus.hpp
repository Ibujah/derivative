#ifndef _PLUS_H_
#define _PLUS_H_

#include "Derivative.hpp"

template<typename O1, typename... Ops>
class Plus
{
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
class Plus<O1,O2,Ops...>
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...)+Plus<O2,Ops...>::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + "+" + Plus<O2,Ops...>::write(args...) + ")";
        }
};

template<typename O1, typename A, typename... Ops>
struct Der<Plus<O1,Ops...>, A>
{
    using type = Plus<typename Der<O1,A>::type>;
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<Plus<O1,O2,Ops...>, A>
{
    using type = Plus<typename Der<O1,A>::type,typename Der<Plus<O2,Ops...>,A>::type>;
};

#endif //_PLUS_H_
