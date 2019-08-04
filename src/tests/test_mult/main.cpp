#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Parameters.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Mult.hpp>

using F1 = Mult<X,Y>;
using F2 = Mult<One,X>;
using F3 = Mult<One,X,X>;
using F4 = Mult<Positive<2>,X,X,A1>;
using F5 = Mult<Negative<3>,X,X,Mult<Y,Y> >;

using DF1 = Der<F1,X>::type;
using DF2 = Der<F2,X>::type;
using DF3 = Der<F3,X>::type;
using DF4 = Der<F4,X>::type;
using DF5 = Der<F5,X>::type;

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
	
	std::cout << DF1::write() << std::endl;
	std::cout << DF2::write() << std::endl;
	std::cout << DF3::write() << std::endl;
	std::cout << DF4::write(param) << std::endl;
	std::cout << DF5::write() << std::endl;
	
    return 0;
}
