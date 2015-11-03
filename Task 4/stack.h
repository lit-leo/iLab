#ifndef stack_h
#define stack_h
typedef struct st {
    double *array;
    int leng;
    int last;
    int incr;
} stack_s;

void ctor(stack_s *this, int qty, int incr); //initialises object wiit type stack with length of qty and sets increment incr

void dtor(stack_s *this); //destructs object with type of stack

int ok(stack_s this); //checks if object has valid data

void dump(stack_s this); //print info about object's data

int push(stack_s *this, double x); //push x into this

double pop(stack_s *this); // pop from this

int isEmpty(stack_s this); // checks if object is empty

#endif

