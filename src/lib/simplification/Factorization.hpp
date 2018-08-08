#ifndef _FACTORIZATION_H_
#define _FACTORIZATION_H_

#include <basic_operations/Plus.hpp>
#include <basic_operations/Mult.hpp>
#include <type_traits>

template<typename EXPR>
struct Factorize
{
    using type = EXPR;
};

template<typename O1, typename O2, typename O3, typename O4>
struct Factorize<Plus<Mult<O1,O2>,Mult<O3,O4> > >
{
    using type =
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

#endif//_FACTORIZATION_H_