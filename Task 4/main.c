#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    stack_s a;
    
    double k;
    ctor(&a, 1, 10);
    dump(a);
    push(&a, 2);
    dump(a);
    push(&a, 4);
    dump(a);
    scanf("%lg", &k);
    push(&a, k);
    pop(&a);
    dump(a);
    pop(&a);
    dump(a);
    printf("\nIsEmpty : %d\n", isEmpty(a));
    dtor(&a);
    
    return 0;
}


