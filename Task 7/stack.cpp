#include "stack.h"
#include <cstdlib>
#include <iostream>

void Cstack::dump()
{
        std::cout << "Size is " << size_ << "\n";
        std::cout << "Top is " << top_ << "\n";
        for (int i = 0; i < size_; i++)
            std::cout << "data[" << i << "] = " << data_[i] << "\n";   
}

int Cstack::ok()
{
    if (top_ >= -1 && size_ > 0 && data_!= NULL)
        return 1;
    else
        return 0;
}

Cstack::Cstack()
{
    if (StacksQty > 2)
    {
        std::cout << "Under free permit you can't have more than 3 stacks.\n";
        exit(11);
    }
    else
    {
        data_ = NULL;
        top_ = -1;
        size_ = DefSize;
        data_ = new double [size_];
        if (data_ == NULL)
        {
            std::cout << "Incorrect memory allocation\n";
            exit(2);
        }
        StacksQty++;
    }
}

Cstack::Cstack(int dim)
{
    if (StacksQty > 2)
    {
        std::cout << "Under free permit you can't have more than 3 stacks.\n";
        exit(11);
    }
    else
    {
        if (dim <= 0)
        {
            std::cout << "Incorrect value met: " << dim << "\n";
            exit(1); 
        }
        data_ = NULL;
        top_ = -1;
        size_ = dim;
        data_ = new double [size_];
        if (data_ == NULL)
        {
            std::cout << "Incorrect memory allocation\n";
            exit(2);
        }
        StacksQty++;
    }
}
Cstack::~Cstack()
{
    top_ = -2;
    size_ = 0;
    delete [] data_;
    StacksQty--;
}

int Cstack::push(double val)
{
    if (!ok())
    {
        exit(10);
    }
    if (top_ == size_ - 1)
    {
        double *ndata = NULL;
        ndata = new double [size_ + DefSize];
        size_ += DefSize;
        for (int i = 0; i < size_; i++)
            ndata[i] = data_[i];
        delete [] data_;
        data_ = ndata;
        ndata = NULL;
        std::cout << "Reallocation has been made...";
        if (data_ == NULL)
        {   
            std::cout << "and it FAILED.\n";
            return 0;
        }
        else
            std::cout << "and everything is OK.\n";
    }

    top_++;
    data_[top_] = val;
    return 1;
}

double Cstack::pop()
{
    if ((size_ > 0) && (top_ > -1) )
    {
        double val = data_[top_];
        top_--;
        return val;
    }
    else
    {
        std::cout << "Error occured while pop\n";
        exit(3);
    }    
}

int Cstack::check()
{
    if (ok())
        std::cout << "Stack is valid\n";
    else
        std::cout << "Stack is NOT valid\n";

    dump();
}

int Cstack::isClear()
{
    if (top_ = -1)
        return 1;
    else
        return 0;
}

void Cstack::change_DefSize(int val)
{
    if(val <= 0)
        std::cout << "Value of " << val << " is wrong. No changes have been made.\n";
    else
        Cstack::DefSize = val;
}

void Cstack::show_DefSize()
{
    std::cout << "DefSize = " << Cstack::DefSize << "\n";
}

void Cstack::show_StacksQty()
{
    std::cout << Cstack::StacksQty << "\n";
}