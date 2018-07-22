#ifndef _APPLICATION_H_
#define _APPLICATION_H_


class Zero
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return 0;
        };
        static std::string write()
        {
            return "0";
        }
};

class One
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return 1;
        };
        static std::string write()
        {
            return "1";
        }
};

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

template<unsigned int n>
class Argument
{
    public:
        template<unsigned int na, typename ...Args>
        static inline double eval(const Parameter<na> &p, Args... args)
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
        template<unsigned int na, typename ...Args>
        static inline double eval(const Parameter<na> &p, Args... args)
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

template<typename O1, typename O2>
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

template<typename O1, typename O2>
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

template<typename F, typename A>
struct Der {};

template<typename A>
struct Der<Zero,A>
{
    using der = Zero;
};

template<typename A>
struct Der<One,A>
{
    using der = Zero;
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

template<typename O1, typename O2, typename A>
struct Der<Plus<O1,O2>, A>
{
    using der = Plus<typename Der<O1,A>::der,typename Der<O2,A>::der>;
};

template<typename O1, typename O2, typename A>
struct Der<Mult<O1,O2>, A>
{
    using der = Plus< Mult<typename Der<O1,A>::der,O2>, Mult<O1,typename Der<O2,A>::der> >;
};

#endif//_APPLICATION_H_
