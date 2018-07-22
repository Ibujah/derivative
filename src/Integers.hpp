#ifndef _INTEGERS_H_
#define _INTEGERS_H_

template<unsigned int n>
class Integer
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return n;
        };
        static std::string write()
        {
            return std::to_string(n);
        }
};

using Zero = Integer<0>;
using One = Integer<1>;

#endif //_INTEGERS_H_
