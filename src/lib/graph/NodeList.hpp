/*
MIT License

Copyright (c) 2018 Bastien Durix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#ifndef _NODE_LIST_
#define _NODE_LIST_

#include <string>

/**
 * @brief Node of the function graph that takes indefinite number of arguments
 */
template<typename Op, typename O1, typename... Ops>
class NodeList
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
			using type = NodeList<Op,O1,Ops...,O>;
		};
	
		template<typename... O>
		struct append<NodeList<Op,O...> >
		{
			using type = NodeList<Op,O1,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = NodeList<Op,O,O1,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<NodeList<Op,O...> >
		{
			using type = NodeList<Op,O...,O1,Ops...>;
		};
};

template<typename Op, typename O1, typename O2, typename... Ops>
class NodeList<Op,O1,O2,Ops...> : public NodeList<Op,O2,Ops...>
{
	protected:
        template<typename ...Args>
        static std::string write_int(Args... args)
        {
            return O1::write(args...) + Op::symb + NodeList<Op,O2,Ops...>::write_int(args...);
        };

    public:
        template<typename ...Args>
        static inline double eval(Args... args)
        {
            return Op::operation(O1::eval(args...),NodeList<Op,O2,Ops...>::eval(args...));
        };

        template<typename ...Args>
        static std::string write(Args... args)
        {
            return "(" + O1::write(args...) + Op::symb + NodeList<Op,O2,Ops...>::write_int(args...) + ")";
        }
		

		template<typename O>
		struct append
		{
			using type = NodeList<Op,O1,O2,Ops...,O>;
		};
	
		template<typename... O>
		struct append<NodeList<Op,O...> >
		{
			using type = NodeList<Op,O1,O2,Ops...,O...>;
		};
		
		template<typename O>
		struct rev_append
		{
			using type = NodeList<Op,O,O1,O2,Ops...>;
		};
	
		template<typename... O>
		struct rev_append<NodeList<Op,O...> >
		{
			using type = NodeList<Op,O...,O1,O2,Ops...>;
		};
};

#endif //_NODE_LIST_H_
