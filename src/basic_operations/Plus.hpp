#ifndef _PLUS_H_
#define _PLUS_H_

#include "../differential/Derivative.hpp"

template<typename O1, typename... Ops>
class Plus
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...);
        };

    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return O1::write(args...);
        };
		
		template<typename O>
		struct append
		{
			using type = Plus<O1,Ops...,O>;
		};
	
		template<typename... O>
		struct append<Plus<O...> >
		{
			using type = Plus<O1,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = Plus<O,O1,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<Plus<O...> >
		{
			using type = Plus<O...,O1,Ops...>;
		};
};

template<typename O1, typename O2, typename... Ops>
class Plus<O1,O2,Ops...> : public Plus<O2,Ops...>
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...) + "+" + Plus<O2,Ops...>::write_int(args...);
        };

    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return O1::eval(args...)+Plus<O2,Ops...>::eval(args...);
        };
        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + "+" + Plus<O2,Ops...>::write_int(args...) + ")";
        };
		
		template<typename O>
		struct append
		{
			using type = Plus<O1,O2,Ops...,O>;
		};
	
		template<typename... O>
		struct append<Plus<O...> >
		{
			using type = Plus<O1,O2,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = Plus<O,O1,O2,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<Plus<O...> >
		{
			using type = Plus<O...,O1,O2,Ops...>;
		};
};

template<typename O1, typename A, typename... Ops>
struct Der<Plus<O1,Ops...>, A>
{
    using type = Plus<typename Der<O1,A>::type>;
};

template<typename O1, typename O2, typename A, typename... Ops>
struct Der<Plus<O1,O2,Ops...>, A>
{
    using type = Plus<typename Der<O1,A>::type,typename Der<Plus<O2,Ops...>,A>::type>;
};

#endif //_PLUS_H_
