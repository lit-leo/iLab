#include "vector.h"
#include "exeption.h"
#include <iostream>

int CVector::m_dim = 2;

int main(int argc, char const *argv[])
{
    CVector a;
    CVector b;
    double c;
    try
    {
    c = 0;
    //CVector d(2);
    a[0] = 3;
    b[0] = 3;
    a[1] = 3;
    b[1] = 3;
    c = a ^ b;
    std::cout << a.len() << std::endl;
    }
    catch (CException &e)
    {
        std::cout << "Exeption cought: " << e.what();
        std::cout << " in " << e.where() << std::endl;

        return e.exit_code();
    }

    return 0;
}