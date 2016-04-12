#include "vector.h"
#include "vector.cpp"
#include "exeption.h"
#include <iostream>

template <class T> int CVector<T>::m_dim = 2;

int main(int argc, char const *argv[])
{
    try
    {
        CVector<int> a;
        CVector<int> b;
        a[0] = 1;
        a[1] = 0;
        b[0] = 3;
        b[1] = 9;
        b -= a;
        std::cout << b;
    }
    /*CVector a;
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
    }*/
    catch (CException &e)
    {
        std::cout << "Exeption cought: " << e.what();
        std::cout << " in " << e.where() << std::endl;

        return e.exit_code();
    }

    return 0;
}