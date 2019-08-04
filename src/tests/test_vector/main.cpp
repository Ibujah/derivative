#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Parameters.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Plus.hpp>
#include <basic_operations/Mult.hpp>

#include <basic_operands/Vector2.hpp>

#include <simplification/Simplify.hpp>
#include <output/Print.hpp>


using F1 = Plus<X,Y>;
using F2 = Mult<X,Y>;

using F3 = Vector2<F1,F2>;

using DF1 = Der<F1,X>::type;
using DF2 = Der<F2,X>::type;
using DF3 = Simp<Der<F3,X>::type>::type;

int main()
{
	std::cout.precision(2);
    
	std::cout << F1::write() << std::endl;
	std::cout << F2::write() << std::endl;
	std::cout << F3::write() << std::endl;

	std::cout << DF1::write() << std::endl;
	std::cout << DF2::write() << std::endl;
	std::cout << DF3::write() << std::endl;
	
	
    return 0;
}
