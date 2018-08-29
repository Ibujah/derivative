#include <iostream>

#include <basic_operands/Integers.hpp>
#include <basic_operands/Arguments.hpp>

#include <basic_operations/Plus.hpp>
#include <basic_operations/Mult.hpp>

#include <simplification/Sort.hpp>

#define _DEBUG_FUNCTIONS_
#include <output/Print.hpp>

using F = Plus<One,Mult<X,Y>,X,Y,Zero,Y,X>;
using Fs = Sort<F>::type;

PRINT(F)
PRINT(Fs)

int main()
{
    std::cout << F::write() << std::endl;
    std::cout << Fs::write() << std::endl;
    return 0;
}
