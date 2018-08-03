#ifndef _LIST_OP_COMM_H_
#define _LIST_OP_COMM_H_

template<typename OpCom, char symb, typename O1, typename... Ops>
class List_Op_Comm
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...);
        };

    public:
		using opcom = OpCom;


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
			using type = List_Op_Comm<OpCom,symb,O1,Ops...,O>;
		};
	
		template<typename... O>
		struct append<List_Op_Comm<OpCom,symb,O...> >
		{
			using type = List_Op_Comm<OpCom,symb,O1,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = List_Op_Comm<OpCom,symb,O,O1,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<List_Op_Comm<OpCom,symb,O...> >
		{
			using type = List_Op_Comm<OpCom,symb,O...,O1,Ops...>;
		};
};

template<typename OpCom, char symb, typename O1, typename O2, typename... Ops>
class List_Op_Comm<OpCom,symb,O1,O2,Ops...> : public List_Op_Comm<OpCom,symb,O2,Ops...>
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...) + symb + List_Op_Comm<OpCom,symb,O2,Ops...>::write_int(args...);
        };

    public:
		using opcom = OpCom;


        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return OpCom::operation(O1::eval(args...),List_Op_Comm<OpCom,symb,O2,Ops...>::eval(args...));
        };

        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + symb + List_Op_Comm<OpCom,symb,O2,Ops...>::write_int(args...) + ")";
        }
		

		template<typename O>
		struct append
		{
			using type = List_Op_Comm<OpCom,symb,O1,O2,Ops...,O>;
		};
	
		template<typename... O>
		struct append<List_Op_Comm<OpCom,symb,O...> >
		{
			using type = List_Op_Comm<OpCom,symb,O1,O2,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = List_Op_Comm<OpCom,symb,O,O1,O2,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<List_Op_Comm<OpCom,symb,O...> >
		{
			using type = List_Op_Comm<OpCom,symb,O...,O1,O2,Ops...>;
		};
};

template<typename OpCom>
struct Neutral
{};

#endif //_LIST_OP_COMM_H_

