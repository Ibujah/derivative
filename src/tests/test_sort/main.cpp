#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Plus.hpp>
#include <basic_operations/Mult.hpp>

#include <simplification/Sort.hpp>
#include <simplification/Simplify.hpp>

#define _DEBUG_FUNCTIONS_
#include <output/Print.hpp>

using F = Plus<One,Mult<X,Y>,X,Y,Zero,Y,X,One>;
using Fs = Sort<F>::type;

PRINT(F)
PRINT(Fs)

using Fil = FilterInt<F>::type;
PRINT(Fil)

int main()
{
    std::cout << F::write() << std::endl;
    std::cout << Fs::write() << std::endl;
    std::cout << Fil::write() << std::endl;
    return 0;
}
