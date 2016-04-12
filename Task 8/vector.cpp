#include "vector.h"
#include <iostream>
#include <cmath>
#include "exeption.h"

template <class T> CVector<T>::CVector()
    {
        //std::cout << "!!Object Created!!\n";
        m_coord = NULL;
        try
        {
            m_coord = new T [m_dim];
            if (m_coord == NULL)
                throw CException("Bad Alloc", 
                                 "CVector<T>::CVector<T>()", BAD_ALLOC);
        }
        catch(CException& e)
        {
            throw e; 
        }
    }

template <class T> CVector<T>::CVector(int range)
    {
        //std::cout << "!!Object Created!!\n";
        m_coord = NULL;
        try
        {
            //std::cout << "RANGE " << range << '\n';
            if (range <= 0)
                throw CException("Bad Alloc range", 
                                 "CVector<T>::CVector<T>(int range)", BAD_ALLOC);
            
            m_coord = new T [range];
            
            if (m_coord == NULL)
                throw CException("Bad Alloc", 
                                 "CVector<T>::CVector<T>(int range)", BAD_ALLOC);
        }
        catch(CException& e)
        {
            throw e; 
        }
    }


template <class T> CVector<T>::CVector(const CVector<T>& that)
    {
        //std::cout << "!!Object Copyed!!\n";
        for (int i = 0; i < m_dim; i++)
            m_coord[i] = that.m_coord[i];
    }

template <class T> CVector<T>::~CVector() 
    {
        //std::cout << "!!Object Destroyed!!\n";
        delete [] this->m_coord;
    };

template <class T> const T& CVector<T>::operator[] (int index) const
{
    try
    {
        //std::cout << "I choosed const [" << index << "]\n";
        if (index < 0 || index > m_dim - 1)
        {
            throw CException("Out of bonds",
                 "const T& CVector<T>::operator[] (int index) const", OUT_OF_BOUNDS);
            return m_coord[0];
        }   
        return m_coord[index];
    }
    catch(CException& e)
    {
        throw e; 
    }
}

template <class T> T& CVector<T>::operator[] (int index)
{
    try
    {
        //std::cout << "I choosed NOT const [" << index << "]\n";
        if (index < 0 || index > m_dim - 1)
            {
                throw CException("Out of bonds",
                     "T& CVector<T>::operator[] (int index)", OUT_OF_BOUNDS);
                return m_coord[0];
            }   
            return m_coord[index];
    }
    catch(CException& e)
    {
        throw e; 
    }    
};

template <class T> CVector<T>& CVector<T>::operator+= (const CVector<T>& right)
{
    for (int i = 0; i < m_dim; ++i)
    {
        m_coord[i] += right.m_coord[i];
    }
    return *this;
}

template <class T> CVector<T> CVector<T>::operator+ (const CVector<T>& right)
{
    CVector<T> temporary;
    for (int i = 0; i < m_dim; i++)
        temporary[i] = this->m_coord[i] + right[i];
    return temporary;
}

template <class T> CVector<T>& CVector<T>::operator-= (const CVector<T>& right)
{
    for (int i = 0; i < m_dim; ++i)
    {
        m_coord[i] -= right.m_coord[i];
    }
    return *this;
}

template <class T> CVector<T> CVector<T>::operator- (const CVector<T>& right)
{
    CVector<T> temporary;
    for (int i = 0; i < m_dim; i++)
        temporary[i] = this->m_coord[i] - right[i];
    return temporary;
}

template <class T> CVector<T> CVector<T>::operator* (double number)
{
    CVector<T> temporary;
    for (int i = 0; i < m_dim; ++i)
    {
        temporary[i] = this->m_coord[i] * number;
    }
    return temporary;   
}

template <class T> T CVector<T>::operator* (const CVector<T>& right)
{
    T temporary = 0;;
    for (int i = 0; i < m_dim; i++)
    {
    temporary += this->m_coord[i] * right[i];
    //std::cout << temporary << '\n';
    }    
    return temporary;
};
       
template <class T> T CVector<T>::operator^ (const CVector<T>& that)
{
    T cos_angle = 0;

    T temp;

        //temp = this * that;
    temp = this->operator*(that);
    cos_angle = temp / this->len() / that.len();

    //std::cout << cos_angle << '\n';
        return cos_angle;
}
    
template <class T> CVector<T>& CVector<T>::operator= (const CVector<T>& right)
{
    for (int i = 0; i < m_dim; ++i)
    {
        m_coord[i] = right.m_coord[i];
    }
}

template <class T> const double CVector<T>::len () const
{
    T sum = 0;
    for (int i = 0; i < m_dim; ++i)
    {
        sum += m_coord[i] * m_coord[i];
    }

    return sqrt(sum);
}

template <class T> std::ostream& operator<< (std::ostream& os, const CVector<T>& vect)
{

    for (int i = 0; i < vect.m_dim; i++)
        os << "[" << i << "] = " << vect[i] << ";\n";
    os << '\0';

    return os;
}

