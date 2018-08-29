#ifndef _PRINT_H_
#define _PRINT_H_

#ifdef _DEBUG_FUNCTIONS_
#define PRINT(F) template<typename F> \
int print_##F() \
{ \
    int type_of_##F = 0; \
    return 0; \
};\
int res_##F = print_##F<F>();
#else
#define PRINT(F)
#endif

#endif //_PRINT_H_
