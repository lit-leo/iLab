#include "vector.h"
#include <iostream>
#include <cmath>

    const double& CVector::operator[] (int index) const
    {
        try
        {
            std::cout << "I choosed const [" << index << "]\n";
            return m_coord[index];
        if ()throw (int a)
        }
    }
    double& CVector::operator[] (int index)
    {
        std::cout << "I choosed NOT const [" << index << "]\n";
        return m_coord[index];      
    };

    CVector& CVector::operator+= (const CVector& right)
    {
        for (int i = 0; i < m_dim; ++i)
        {
            m_coord[i] += right.m_coord[i];
        }

        return *this;
    }

    CVector CVector::operator+ (const CVector& right)
    {
        CVector temporary;
        for (int i = 0; i < m_dim; i++)
            temporary[i] = this->m_coord[i] + right[i];
        return temporary;
    }
    
    CVector CVector::operator* (double number)
    {
        CVector temporary;
        for (int i = 0; i < m_dim; ++i)
        {
            temporary[i] = this->m_coord[i] * number;
        }

        return temporary;   
    }
    
    double CVector::operator* (const CVector& right)
    {
        double temporary;
        for (int i = 1; i < m_dim; i++)
            temporary += this->m_coord[i] * right[i];
        return temporary;
    };
    
    CVector CVector::operator- (const CVector& right)
    {
        CVector temporary;
        for (int i = 0; i < m_dim; i++)
            temporary[i] = this->m_coord[i] - right[i];
        return temporary;
    }
    
    double CVector::operator^ (const CVector& that)
    {
        double cos_angle = 0;

        double temp;

        //temp = this * that;
        temp = this->operator*(that);
        cos_angle = temp / this->len() / that.len();

        return cos_angle;
        //return acos(cos_angle);
    }
    
    CVector& CVector::operator= (const CVector& right)
    {
        for (int i = 0; i < m_dim; ++i)
        {
            m_coord[i] = right.m_coord[i];
        }
    }

    const double CVector::len () const
    {
        double sum = 0;
        for (int i = 0; i < m_dim; ++i)
        {
            sum += m_coord[i] * m_coord[i];
        }

        return sqrt(sum);
    }
