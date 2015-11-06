#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define MAX_SIZE 32

int cmdqty(FILE *filein)
{
    int leng = 0;
    double tmp = 0;
    while (fscanf(filein, "%lg", &tmp) == 1)
    {
        leng++;
        fflush(filein);
    }
    rewind(filein);
    return leng;
}


int main(int argc, char* argv[])
{
    double *mem;
    int memleng = 0, ip = 0;
    char answ;
    stack_s stack;    

    FILE *filein = NULL;
    filein = fopen(argv[1], "rt");

    if ((argc != 2) || (filein == NULL))
    {
        printf("./<programm name> <input file>\n");
        exit(1);
    }

    memleng = cmdqty(filein);

    //printf("memleng is %d\n", memleng);
    
    mem = (double*)calloc(memleng, sizeof(double));

    for (ip = 0; ip < memleng; ip++)
        fscanf(filein, "%lg", &mem[ip]);
    ctor(&stack, 10, 5);
    //dump(stack);

    /*for (ip = 0; ip < memleng; ip++)
        fprintf(stdout, "mem[%d] = %lg \n", ip, mem[ip]);
    printf("1\n");*/
    ip = 0;
    do
    { //printf("\nIn cycle\n");
        //printf("\nmem[%d] is %d\n",ip ,(int)mem[ip]);
        switch((int)mem[ip])
        {
            case 1:
            push(&stack, mem[ip+1]);
            ip += 2;
            break;

            case 2:
            pop(&stack);
            ip += 1;
            break;

            case 3:
            push(&stack, pop(&stack) + pop(&stack));
            ip += 1;
            break;

            case 4:
            push(&stack,-1*pop(&stack) + pop(&stack));
            ip += 1;
            break;

            case 5:
            push(&stack, pop(&stack) * pop(&stack));
            ip += 1;
            break;

            case 6:
            push(&stack, 1/pop(&stack) * pop(&stack));
            ip += 1;
            break;

            case 7:
            printf("Something wrong happened. Condition of termination is broken.");
            dump(stack);
            break;

            default:
            fprintf(stdout, "Unknown command found/End coomand loosed\nIn position %d", ip);
            fprintf(stdout, "\nType Y to continue or anything else to exit\n");
            scanf("%c", &answ);
            if (answ == 'Y')
                break;
            else
                exit(2);
            break;
        }
    //printf("Ended switch, ip is now %d\n", ip);
    } while ( mem[ip] != 7);

    dump(stack);

    dtor(&stack);
    
    fclose(filein);

    return 0;
}

