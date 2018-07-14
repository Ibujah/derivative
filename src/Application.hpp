#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <Eigen/Dense>

template<typename Output, typename Input>
class Application
{
    protected:
        
    public:
        virtual Output operator()(const Input &) const = 0;
};


template<unsigned int Outdim, unsigned int Indim>
class RealApplication : public Application<Eigen::Matrix<double,Outdim,1>,Eigen::Matrix<double,Indim,1> >
{
    protected:
        using Output = Eigen::Matrix<double,Outdim,1>;
        using Input = Eigen::Matrix<double,Indim,1>;
    public:
        virtual Output operator()(const Input &) const = 0;
};

template<unsigned int Outdim, unsigned int Indim>
class AffineFun : public RealApplication<Outdim,Indim>
{
    protected:
        using Output = Eigen::Matrix<double,Outdim,1>;
        using Input = Eigen::Matrix<double,Indim,1>;
        
        Eigen::Matrix<double,Outdim,Indim> A;
        Eigen::Matrix<double,Outdim,1> b;
    public:
        AffineFun(const Eigen::Matrix<double,Outdim,Indim> &A_, Eigen::Matrix<double,Outdim,1> b_) : A(A_), b(b_) {};
        virtual Output operator()(const Input &in) const
        {
            return A*in+b;
        };
};

#endif//_APPLICATION_H_
