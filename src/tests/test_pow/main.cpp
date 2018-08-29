#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Parameters.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Pow.hpp>
#include <basic_operations/Exp.hpp>

using F1 = Pow<X,Integer<2> >;
using F2 = Pow<Exp<One>,X>;

using DF1 = Der<F1,X>::type;
using DF2 = Der<F2,X>::type;

int main()
{
	std::cout.precision(2);
    
	const double x0 = 2.0;
	std::cout << "x0 = " << x0 << std::endl;
	
	std::cout << F1::write() << " " << F1::eval(x0) << std::endl;
	std::cout << F2::write() << " " << F2::eval(x0) << std::endl;
	std::cout << Exp<X>::write() << " " << Exp<X>::eval(x0) << std::endl;
	
	std::cout << DF1::write() << " " << DF1::eval(x0) << std::endl;
	std::cout << DF2::write() << " " << DF2::eval(x0) << std::endl;
	
    return 0;
}
