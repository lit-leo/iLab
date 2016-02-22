#include <iostream>
#include "stack.h"

int Cstack::StacksQty = 0;
int Cstack::DefSize = 1;

int main(int argc, char const *argv[])
{
    Cstack s1, s3, s4, s67;
    s1.show_StacksQty();
    s1.show_StacksQty();
    s1.change_DefSize(2);
    s1.push(7.0);
    s1.dump();

    s1.push(7.5);
    s1.dump();
        s1.push(7.5);
    s1.dump();
        s1.push(7.5);
    s1.dump();
        s1.push(7.5);
    s1.dump();

    
    s1.show_StacksQty();
    return 0;
}