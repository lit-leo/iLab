#include "vector.h"
#include <iostream>
#include <cmath>
#include "exeption.h"

CVector::CVector()
    {
        //std::cout << "!!Object Created!!\n";
        m_coord = NULL;
        try
        {
            m_coord = new double [m_dim];
            if (m_coord == NULL)
                throw CException("Bad Alloc", 
                                 "CVector::CVector()", BAD_ALLOC);
        }
        catch(CException& e)
        {
            throw e; 
        }
    }

CVector::CVector(int range)
    {
        //std::cout << "!!Object Created!!\n";
        m_coord = NULL;
        try
        {
            //std::cout << "RANGE " << range << '\n';
            if (range <= 0)
                throw CException("Bad Alloc range", 
                                 "CVector::CVector(int range)", BAD_ALLOC);
            
            m_coord = new double [range];
            
            if (m_coord == NULL)
                throw CException("Bad Alloc", 
                                 "CVector::CVector(int range)", BAD_ALLOC);
        }
        catch(CException& e)
        {
            throw e; 
        }
    }


CVector::CVector(const CVector& that)
    {
        //std::cout << "!!Object Copyed!!\n";
        for (int i = 0; i < m_dim; i++)
            m_coord[i] = that.m_coord[i];
    }

CVector::~CVector() 
    {
        //std::cout << "!!Object Destroyed!!\n";
        delete [] this->m_coord;
    };

const double& CVector::operator[] (int index) const
{
    try
    {
        //std::cout << "I choosed const [" << index << "]\n";
        if (index < 0 || index > m_dim - 1)
        {
            throw CException("Out of bonds",
                 "const double& CVector::operator[] (int index) const", OUT_OF_BOUNDS);
            return m_coord[0];
        }   
        return m_coord[index];
    }
    catch(CException& e)
    {
        throw e; 
    }
}
double& CVector::operator[] (int index)
{
    try
    {
        //std::cout << "I choosed NOT const [" << index << "]\n";
        if (index < 0 || index > m_dim - 1)
            {
                throw CException("Out of bonds",
                     "double& CVector::operator[] (int index)", OUT_OF_BOUNDS);
                return m_coord[0];
            }   
            return m_coord[index];
    }
    catch(CException& e)
    {
        throw e; 
    }    
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
    double temporary = 0;;
    for (int i = 0; i < m_dim; i++)
    {
    temporary += this->m_coord[i] * right[i];
    //std::cout << temporary << '\n';
    }    
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

    //std::cout << cos_angle << '\n';
        return cos_angle;
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

std::ostream& operator<< (std::ostream& os, const CVector& vect)
{

    for (int i = 0; i < vect.m_dim; i++)
        os << "[" << i << "] = " << vect[i] << ";\n";
    os << '\0';

    return os;
}