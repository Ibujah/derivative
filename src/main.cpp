#include <iostream>
#include "Application.hpp"

using X = Argument<0>;
using Y = Argument<1>;
using Z = Argument<2>;
using F = Plus<X,Y>;
using G = Plus<X,X>;
using H = Plus<X,One>;
using dFdX = Der<F,X>::der;
using dGdX = Der<G,X>::der;
using dHdX = Der<H,X>::der;
using ddGddX = Der<Der<G,X>::der,X>::der;

int main()
{
    // what I want:
    // f(x) = x+4
    // Plus<X,4> f;
    // g(x) = (4+x)*(2*x)
    // Mul<Plus<X,4>,Mul<2,X> > g;
    // h(x) = g'(x)
    // auto h = Der<X>(g);
    // u(x,y) = x+y
    // Plus<X,Y> u;
    
    std::cout << "Hello world!" << std::endl;
    
    std::cout << "X " << X::eval(0,1,2) << std::endl;
    std::cout << "Y " << Y::eval(0,1,2) << std::endl;
    std::cout << "F " << F::eval(2,1) << std::endl;
    std::cout << "G " << G::eval(2) << std::endl;
    std::cout << "H " << H::eval(2) << std::endl;
    std::cout << "dFdX " << dFdX::eval(0) << std::endl;
    std::cout << "dGdX " << dGdX::eval(0) << std::endl;
    std::cout << "dHdX " << dHdX::eval(0) << std::endl;
    std::cout << "ddGddX " << ddGddX::eval(0) << std::endl;
    // std::cout << Y::eval(0) << std::endl; // error

    return 0;
}
