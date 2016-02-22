#ifndef stack_h
#define stack_h

class Cstack
{
private:
    double * data_;
    int top_;
    int size_;
    static int StacksQty;
    static int DefSize;    

public:


    Cstack();
    Cstack(int dim);
    ~Cstack();
    
    void dump();
    int ok();
    int push(double val);
    double pop();
    int check();
    int isClear();
    void change_DefSize(int val);
    void show_DefSize();
    void show_StacksQty();
};

#endif