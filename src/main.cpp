#include <iostream>
#include "Application.hpp"

using X = Argument<0>;
using Y = Argument<1>;
using Z = Argument<2>;
using A1 = Parameter<1>;
using A2 = Parameter<2>;
using A3 = Parameter<3>;
using F = Plus<X,Y>;
using G = Plus<X,X>;
using H = Mult<X,X>;
using dFdX = Der<F,X>::der;
using dGdX = Der<G,X>::der;
using dHdX = Factorize<Der<H,X>::der>::fac;
using ddGddX = Der<dGdX,X>::der;
using ddHddX = Der<dHdX,X>::der;
using F1 = Plus<A1,A2>;

int main()
{
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
    
    std::cout << F1::write(param<2>(4.0,2.0)) << " " << F1::eval(param<2>(4.0,2.0)) << std::endl;

    return 0;
}
