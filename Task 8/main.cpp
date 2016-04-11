#include "vector.h"
#include <iostream>

int CVector::m_dim = 1;

int main(int argc, char const *argv[])
{
    CVector a;
    CVector b;
    double c;
    try
    {
        for (int i = 0; i < 1; ++i)
        {
            a[i] = 5;
            b[i] = 5;
        }
        //std::cout << "/*/*/*/*/*/*/\n";/**/
        //std::cout << b[0] << std::endl;
        c = b * a;
        std::cout << "a*b = " << a * b << " len = "<< a.len() << " " << b.len() << std::endl;
        c = a ^ b;
        //b += a;
        //b = b * 10.0;
        //b = b - a * 10.0;
        std::cout << "cos" << c << std::endl;
    }
    catch (std::exeption& e)

    return 0;
}