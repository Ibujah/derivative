#include <iostream>
#include "Application.hpp"

using F = Plus<X,Y>;
using G = Plus<X,X>;
using H = Mult<X,X>;
using dFdX = Der<F,X>::type;
using dGdX = Der<G,X>::type;
using dHdX = Der<H,X>::type;
using FacdHdX = Factorize<Der<H,X>::type>::type;
using ddGddX = Der<dGdX,X>::type;
using ddHddX = Der<dHdX,X>::type;
using F1 = Plus<A1,A2>;
using F2 = Plus<Mult<A1,A1>,A2,X>;
using dF2 = Der<F2,X>::type;
using F3 = Plus<One,One,One,X>;
using F4 = Plus<X,One,One,One>;
using F5 = Plus<X,One,Y,One,One>;
using F6 = Plus<X,One>::append<One>::type;
using F7 = Plus<X,Zero,Zero,Zero>::append<Plus<Plus<One, Plus<One > > > >::type;

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

    std::cout << dHdX::write() << " " << FacdHdX::write() << std::endl;

    std::cout << F2::write(param<2>(4.0,2.0),x) << " " << F2::eval(param<2>(4.0,2.0),x) << std::endl;
    std::cout << dF2::write(param<2>(4.0,2.0),x) << " " << dF2::eval(param<2>(4.0,2.0),x) << std::endl;
	std::cout << F3::write() << " " << Simp<F3>::type::write() << " " << F3::eval(x) << std::endl;
	std::cout << F4::write() << " " << Sort<F4>::type::write() << " " << Simp<Sort<F4>::type >::type::write() << " " << F4::eval(x) << std::endl;
	std::cout << F5::write() << " " << Sort<F5>::type::write() << " " << Simp<Sort<F5>::type >::type::write() << " " << F5::eval(x,y) << std::endl;
	std::cout << F6::write() << " " << F7::write() << std::endl;
    return 0;
}
