#ifndef stack_h
#define stack_h
typedef struct st {
    double *array;
    int leng;
    int last;
    int incr;
} stack_s;

void ctor(stack_s *this, int qty, int incr);

void dtor(stack_s *this);

int ok(stack_s this);

void dump(stack_s this);

int push(stack_s *this, double x);

double pop(stack_s *this);

int isEmpty(stack_s this);

#endif

