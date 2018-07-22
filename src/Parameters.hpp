#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

template<unsigned int n>
class Parameter
{
    public:
        double a;
        Parameter<n-1> p;
        
    public:
        template<typename ...Args>
        Parameter(const double &a_, Args... args) : a(a_), p(args...)
        {};
        
        template<unsigned int na, typename ...Args>
        static inline double eval(const Parameter<na> &p, Args... args)
        {
            return Parameter<n-1>::eval(p.p);
        };
        
        template<unsigned int na, typename ...Args>
        static std::string write(const Parameter<na> &p, Args... args)
        {
            return Parameter<n-1>::write(p.p);
        }
};

template<>
class Parameter<0>
{};

template<>
class Parameter<1>
{
    public:
        double a;
        
    public:
        Parameter(const double &a_) : a(a_)
        {};

        template<unsigned int na, typename ...Args>
        static inline double eval(const Parameter<na> &p, Args... args)
        {
            return p.a;
        };
        
        
        template<unsigned int na,typename ...Args>
        static std::string write(const Parameter<na> &p, Args... args)
        {
            return std::to_string(p.a);
        }
};

Parameter<1> param(const double &x)
{
    return Parameter<1>(x);
}

template<unsigned int n, typename ...Args>
Parameter<n> param(const double &x, Args... args)
{
    return Parameter<n>(x,Parameter<n-1>(args...));
}

using A1 = Parameter<1>;
using A2 = Parameter<2>;
using A3 = Parameter<3>;

#endif //_PARAMETERS_H_
