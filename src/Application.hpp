#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <Eigen/Dense>
#include <memory>

template<typename output, typename input>
class Application
{
    public:
        using Output = output;
        using Input = input;
        using Ptr = std::shared_ptr<Application>;

    public:
        virtual inline Output operator()(const Input &) const = 0;
};


template<unsigned int Outdim, unsigned int Indim>
class RealApplication : public Application<Eigen::Matrix<double,Outdim,1>,Eigen::Matrix<double,Indim,1> >
{
    public:
        using Output = Eigen::Matrix<double,Outdim,1>;
        using Input = Eigen::Matrix<double,Indim,1>;
        using Ptr = std::shared_ptr<RealApplication>;
        
    public:
        virtual inline Output operator()(const Input &) const = 0;
};

template<unsigned int Outdim, unsigned int Indim>
class AffineFun : public RealApplication<Outdim,Indim>
{
    public:
        using Output = Eigen::Matrix<double,Outdim,1>;
        using Input = Eigen::Matrix<double,Indim,1>;
        using Ptr = std::shared_ptr<AffineFun>;
        
    protected:
        Eigen::Matrix<double,Outdim,Indim> A;
        Eigen::Matrix<double,Outdim,1> b;

    public:
        AffineFun(const Eigen::Matrix<double,Outdim,Indim> &A_, Eigen::Matrix<double,Outdim,1> b_) : A(A_), b(b_) {};
        virtual inline Output operator()(const Input &in) const
        {
            return A*in+b;
        };
};

template<typename Fct, typename... Args>
class Compositor : public Application<typename Fct::Output, typename Fct::Input>
{
    public:
        using Output = typename Fct::Output;
        using Input = typename Fct::Input;
        using Ptr = std::shared_ptr<Compositor>;
        
    protected:
        typename Fct::Ptr m_fct;

    public:
        Compositor() : m_fct(std::make_shared<Fct>()) {};

        Compositor(const typename Fct::Ptr fct) : m_fct(fct) {};

        Compositor(const Fct &fct) : Compositor(typename Fct::Ptr(std::make_shared<Fct>(fct))) {};

        inline Output operator()(const Input &t) const
        {
            return (*m_fct)(t);
        };

        inline const typename Fct::Ptr getFun() const
        {
            return m_fct;
        }
};

template<typename Fct, typename Fct_, typename... Args>
class Compositor<Fct,Fct_,Args...> : public Application<typename Fct::Output,typename Compositor<Fct_,Args...>::Input>
{
    public:
        using Output = typename Fct::Output;
        using Input = typename Compositor<Fct_,Args...>::Input;
        using Ptr = std::shared_ptr<Compositor>;

    protected:
        typename Fct::Ptr m_fct;
        Compositor<Fct_,Args...> m_next;

    public:
        Compositor() : m_fct(std::make_shared<Fct>()), m_next() {};

        Compositor(const typename Fct::Ptr &fct, const typename Fct_::Ptr &fct_, const Args&... fcts) :  m_fct(fct), m_next(fct_, fcts...) {};

        Compositor(const Fct &fct, const Fct_ &fct_, const Args&... fcts) :  m_fct(std::make_shared<Fct>(fct)), m_next(fct_, fcts...) {};

        inline Output operator()(const Input &t) const
        {
            return (*m_fct)(  m_next(t) );
        };

        inline const Compositor<Fct_,Args...>& next() const
        {
            return m_next;
        }

        inline const typename Fct::Ptr getFun() const
        {
            return m_fct;
        }
};

#endif//_APPLICATION_H_
