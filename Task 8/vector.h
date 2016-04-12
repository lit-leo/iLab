#ifndef vector_h
#define vector_h
#include <iostream>

template <class T> class CVector
{
public:
    T* m_coord; //as a debug option, it should be private in relize
    static int m_dim;

    CVector();
    CVector(int range);
    CVector(const CVector<T>& that);
    ~CVector();


    const T& operator[] (int index) const;
    
    T& operator[] (int index);

    CVector<T>& operator+= (const CVector& right);

    CVector<T> operator+ (const CVector& right);

    CVector<T>& operator-= (const CVector& right);

    CVector<T> operator- (const CVector& right);

    CVector<T> operator* (double number);

    T operator* (const CVector& right);
    
    T operator^ (const CVector& right);

    CVector<T>& operator= (const CVector& right);

    template <T> friend std::ostream& operator<< (std::ostream& os, const CVector<T>& vect);

    const double len () const;
};

#endif