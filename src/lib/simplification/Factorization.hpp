/*
MIT License

Copyright (c) 2018 Bastien Durix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

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
