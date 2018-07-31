#ifndef _INTEGERS_H_
#define _INTEGERS_H_

#include "Derivative.hpp"

template<unsigned int n>
class Integer
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return (double)n;
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return std::to_string(n);
        }
};

template<unsigned int n,typename A>
struct Der<Integer<n>,A>
{
    using type = Integer<0>;
};

using Zero = Integer<0>;
using One = Integer<1>;


#endif //_INTEGERS_H_
