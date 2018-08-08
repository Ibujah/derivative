#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Parameters.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Plus.hpp>
#include <basic_operations/Mult.hpp>
#include <basic_operations/Inverse.hpp>
#include <basic_operations/Exp.hpp>

using F1 = Exp<X>;
using F2 = Exp<Mult<Negative<1>,X,Inverse<Integer<2> > > >;

int main()
{
	std::cout.precision(2);
    
	const double x0 = 1.0;
	
	std::cout << F1::write() << " " << F1::eval(x0) << std::endl;
	std::cout << F2::write() << " " << F2::eval(x0) << std::endl;
	
    return 0;
}
