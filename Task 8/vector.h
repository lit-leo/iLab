#ifndef vector_h
#define vector_h
#include <iostream>

class CVector
{
public:
    double *m_coord; //as a debug option, it should be private in relize
    static int m_dim;

    CVector();
    CVector(int range);
    CVector(const CVector& that);
    ~CVector();


    const double& operator[] (int index) const;
    
    double& operator[] (int index);

    CVector& operator+= (const CVector& right);

    CVector operator+ (const CVector& right);
    
    CVector operator* (double number);
    
    double operator* (const CVector& right);
    
    CVector operator- (const CVector& right);
    
    double operator^ (const CVector& right);

    CVector& operator= (const CVector& right);

    friend std::ostream& operator<< (std::ostream& os, const CVector& vect);

    const double len () const;
};

#endif