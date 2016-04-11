#ifndef vector_h
#define vector_h
#include <iostream>
class CVector
{
public:
    double *m_coord; //as a debug option, it should be private in relize
    static int m_dim;

    CVector()
    {
        std::cout << "!!Object Created!!\n";
        m_coord = new double [m_dim];
    }
    CVector(const CVector& that)
    {
        std::cout << "!!Object Copyed!!\n";
        for (int i = 0; i < m_dim; i++)
            m_coord[i] = that.m_coord[i];
    }
    ~CVector() 
    {
        std::cout << "!!Object Destroyed!!\n";
        delete [] this->m_coord;
    };


    const double& operator[] (int index) const;
    
    double& operator[] (int index);

    CVector& operator+= (const CVector& right);

    CVector operator+ (const CVector& right);
    
    CVector operator* (double number);
    
    double operator* (const CVector& right);
    
    CVector operator- (const CVector& right);
    
    double operator^ (const CVector& right);

    CVector& operator= (const CVector& right);

    const double len () const;
};

#endif