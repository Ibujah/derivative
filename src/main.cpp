#include <iostream>
#include "Application.hpp"

int main()
{
    Eigen::Vector2d a(1,2);
    Eigen::Matrix<double,1,1> b(1);
    AffineFun<1,2> aff(a.transpose(),b);
    std::cout << "Hello world!" << std::endl;
    std::cout << aff(Eigen::Vector2d(0,2)) << std::endl;
    return 0;
}
