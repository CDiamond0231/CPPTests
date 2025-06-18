//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             CalculateF (h)
//             Author: Christopher A
//             Date: June 16, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//		Please implement the following mathematical function, in the way 
//		you think is best (explain your choice).
//		
//		F(0) = 0
//		F(n) = n + F(n-1)
//		n=1..20
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef     __CALCULATE_F_H_
#define     __CALCULATE_F_H_



// When reading the question, you might be tempted to use recursion or a ‘for loop’ to handle this. 
// However, recursion not only adds overhead cost (extra variables per stack) but depending on the 
// number you pass in (e.g Int.MaxValue) you could end up initiating a stack overflow. 
// 
// Instead, this question asks for a fundamental mathematical equation. The result is `n * ((n + 1) / 2)`. 
// The function returns a long long to guarantee 64-bit assignment, in case of passing in a large number 
// like INT_MAX which would result in an output that exceeds 32-bit capacity. Not required for the range asked 
// in this question, but required if you assume this function would be used in an actual program.
long long CalculateF(int n)
{
    if (n < 1)
        return 0;

    long long ll = static_cast<long long>(n);
    long long result = ll * (ll + 1) / 2;
    return result;
}

#endif  //  __CALCULATE_F_H_