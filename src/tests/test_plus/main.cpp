#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Parameters.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Plus.hpp>

using F1 = Plus<X,Y>;
using F2 = Plus<One,X>;
using F3 = Plus<One,X,X>;
using F4 = Plus<Integer<2>,X,X,A1>;
using F5 = Plus<Negative<3>,X,X,Plus<Y,Y> >;

int main()
{
	std::cout.precision(2);
    
	const double x0 = 1.0, x1 = 2.0;
	std::cout << "x0 = " << x0 << std::endl;
	std::cout << "x1 = " << x1 << std::endl;
	
	Parameter<1> param(3.0);
	
	std::cout << F1::write() << " " << F1::eval(x0,x1) << std::endl;
	std::cout << F2::write() << " " << F2::eval(x0,x1) << std::endl;
	std::cout << F3::write() << " " << F3::eval(x0,x1) << std::endl;
	std::cout << F4::write(param) << " " << F4::eval(param,x0,x1) << std::endl;
	std::cout << F5::write() << " " << F5::eval(x0,x1) << std::endl;
	
    return 0;
}
