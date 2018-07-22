#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Integers.hpp"
#include "Parameters.hpp"
#include "Arguments.hpp"

#include <type_traits>

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

template<typename EXPR>
struct Factorize
{
    using fac = EXPR;
};

template<typename O1, typename O2, typename O3, typename O4>
struct Factorize<Plus<Mult<O1,O2>,Mult<O3,O4> > >
{
    using fac =
        typename std::conditional
        <
            std::is_same<O1,O3>::value,
            Mult<O1,Plus<O2,O4> >,
            typename std::conditional
            <
                std::is_same<O1,O4>::value,
                Mult<O1,Plus<O2,O3> >,
                typename std::conditional
                <
                    std::is_same<O2,O3>::value,
                    Mult<O2,Plus<O1,O4> >,
                    typename std::conditional
                    <
                        std::is_same<O2,O4>::value,
                        Mult<O2,Plus<O1,O3> >,
                        Plus<Mult<O1,O2>, Mult<O3,O4> >
                    >::type
                >::type
            >::type
        >::type;
};

/*template<typename O1, typename O2>
struct Factorize<Plus<Mult<O1,O2>,Mult<O1,O2> > >
{
    using fac = Mult<O1,Plus<O2,O2> >;
};

template<typename O1, typename O2>
struct Factorize<Plus<Mult<O1,O2>,Mult<O2,O1> > >
{
    using fac = Mult<O1,Plus<O2,O2> >;
};

template<typename O1, typename O2, typename O3>
struct Factorize<Plus<Mult<O1,O2>,Mult<O1,O3> > >
{
    using fac = Mult<O1,Plus<O2,O3> >;
};

template<typename O1, typename O2, typename O3>
struct Factorize<Plus<Mult<O1,O2>,Mult<O3,O1> > >
{
    using fac = Mult<O1,Plus<O2,O3> >;
};

template<typename O1, typename O2, typename O3>
struct Factorize<Plus<Mult<O2,O1>,Mult<O1,O3> > >
{
    using fac = Mult<O1,Plus<O2,O3> >;
};

template<typename O1, typename O2, typename O3>
struct Factorize<Plus<Mult<O2,O1>,Mult<O3,O1> > >
{
    using fac = Mult<O1,Plus<O2,O3> >;
};*/

#endif//_APPLICATION_H_
