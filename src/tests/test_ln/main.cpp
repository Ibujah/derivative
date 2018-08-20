#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Parameters.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Plus.hpp>
#include <basic_operations/Ln.hpp>

using F1 = Ln<X>;
using F2 = Ln<Plus<X,Y> >;

int main()
{
	std::cout.precision(2);
    
	const double x0 = 1.0;
	const double x1 = 2.0;
	std::cout << "x0 = " << x0 << std::endl;
	std::cout << "x1 = " << x1 << std::endl;
	
	std::cout << F1::write() << " " << F1::eval(x0) << std::endl;
	std::cout << F2::write() << " " << F2::eval(x0,x1) << std::endl;
	
    return 0;
}
