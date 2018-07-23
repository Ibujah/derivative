#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

#include "Derivative.hpp"
#include "Integers.hpp"

template<unsigned int n>
class Argument
{
    public:
        template<typename T, typename ...Args>
        static inline double eval(const T &p, Args... args)
        {
            return Argument<n>::eval(args...);
        };
        template<typename ...Args>
        static inline double eval(const double &x, Args... args)
        {
            return Argument<n-1>::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "x" + std::to_string(n);
        }
};

template<>
class Argument<0>
{
    public:
        template<typename T, typename ...Args>
        static inline double eval(const T &p, Args... args)
        {
            return Argument<0>::eval(args...);
        };
        template<typename ...Args>
        static inline double eval(const double &x, Args... args)
        {
            return x;
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "x0";
        }
};

template<unsigned int n>
struct Der<Argument<n>,Argument<n> >
{
    using der = One;
};

template<unsigned int n, unsigned int nA>
struct Der<Argument<n>,Argument<nA> >
{
    using der = Zero;
};

using X = Argument<0>;
using Y = Argument<1>;
using Z = Argument<2>;

#endif //_ARGUMENTS_H_
