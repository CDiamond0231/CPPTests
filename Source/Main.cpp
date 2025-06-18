
#include <iostream>
#include "CalculateF.h"


int main()
{
    for (int i = 0; i <= 20; ++i)
    {
        long long result = CalculateF(i);
        std::cout << "F(" << i << ") = " << result << std::endl;
    }

    std::cin.get();
    return 0;
}


