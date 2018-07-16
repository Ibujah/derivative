#include <iostream>
#include "Application.hpp"

using X = Argument<0>;
using Y = Argument<1>;
using Z = Argument<2>;
using F = Plus<X,Y>;
using G = Plus<X,X>;
using H = Mult<X,X>;
using dFdX = Der<F,X>::der;
using dGdX = Der<G,X>::der;
using dHdX = Der<H,X>::der;
using ddGddX = Der<dGdX,X>::der;
using ddHddX = Der<dHdX,X>::der;

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
    
    double x = 1;
    double y = 2;
    std::cout << X::write() << " " << X::eval(x,y) << std::endl;
    std::cout << Y::write() << " " << Y::eval(x,y) << std::endl;
    std::cout << F::write() << " " << F::eval(x,y) << std::endl;
    std::cout << dFdX::write() << " " << dFdX::eval(x) << std::endl;
    std::cout << std::endl;

    std::cout << G::write() << " " << G::eval(x) << std::endl;
    std::cout << dGdX::write() << " " << dGdX::eval(x) << std::endl;
    std::cout << ddGddX::write() << " " << ddGddX::eval(x) << std::endl;
    std::cout << std::endl;

    std::cout << H::write() << " " << H::eval(x) << std::endl;
    std::cout << dHdX::write() << " " << dHdX::eval(x) << std::endl;
    std::cout << ddHddX::write() << " " << ddHddX::eval(x) << std::endl;
    // std::cout << Y::eval(0) << std::endl; // error

    return 0;
}
