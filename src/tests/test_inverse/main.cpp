#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Parameters.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Plus.hpp>
#include <basic_operations/Mult.hpp>
#include <basic_operations/Inverse.hpp>

using F1 = Mult<Integer<2>,Inverse<X> >;
using F2 = Mult<X,Inverse<X> >;
using F3 = Mult<X,Inverse<Plus<X,Y> > >;

int main()
{
	std::cout.precision(2);
    
    const double x0 = 1, x1 = 2;
	std::cout << "x0 = " << x0 << std::endl;
	std::cout << "x1 = " << x1 << std::endl;
	
	std::cout << F1::write() << " " << F1::eval(x0) << std::endl;
	std::cout << F2::write() << " " << F2::eval(x0) << std::endl;
	std::cout << F3::write() << " " << F3::eval(x0,x1) << std::endl;

    return 0;
}
