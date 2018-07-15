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
};

class One
{
    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return 1;
        };
};

template<unsigned int n>
class Argument
{
    public:
        template<typename ...Args>
        static inline double eval(const double &x, Args... args)
        {
            return Argument<n-1>::eval(args...);
        };
};

template<>
class Argument<0>
{
    public:
        template<typename ...Args>
        static inline double eval(const double &x, Args... args)
        {
            return x;
        };
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
