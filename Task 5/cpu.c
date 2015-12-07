#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define MAX_SIZE 32

enum commands {
    cmd_push_c = 1, //Push constant to the top of stack. Ex* push 7 
    cmd_push_r = 2, //Push value in certain register to the top of stack. Ex* push ax 
    cmd_pop_c = 3, //Pop the top of stack to nowhere. Loosing last element of stack Ex* pop 
    cmd_pop_r = 4, //Pop the top of stack to certain register. Ex* pop bx
    cmd_in = 5,    //Reads value from stdin, pushes it to the top of the stack. Ex* in
    cmd_out = 6,   //Prints top of the stack. Ex* out
    cmd_add_c = 7,  //Adds 2 last elements of stack. Ex* add
    cmd_add_r = 8,  //Moves to the first register sum of 2nd and 3rd. Ex* add ax bx cx
    cmd_sub_c = 9, //Push to the stack the result of subtracktion between element before last and last. Ex* sub
    cmd_sub_r = 10,//Push to the first register the result of subtracktion between two others. Ex* sub ax bx cx <==> ax = bx - cx
    cmd_mul_c = 11,  //Push to the stack the result of multiplication between element before last and last. Ex* mul
    cmd_mul_r = 12, //Multiplies. Ex* mul ax bx cx
    cmd_div_c = 13,//Push to the stack the result of diversification between element before last and last. Ex* div
    cmd_div_r = 14,//Push to the first register the result of diversification between two others. Ex* div ax bx cx <==> ax = bx / cx
    cmd_inc = 15,  //Increases certain register by 1
    cmd_dec = 16,  //Decreases certain register by 1
    cmd_mov_c = 17,//Moves constant to certain reister. Ex* mov ax 7
    cmd_mov_r = 18,//Moves value from 2nd reg to 1st. Ex* mov ax bx <==> ax = bx
    cmd_label = 19,//Showes, that following expression is an adress. In .bin file it will be seen as: 19 *null* *null* *null*
    cmd_jmp = 20, //Jumps on label. Ex* jmp #1
    cmd_je_r = 21,//Jumps on label if value in register equals to zero. Ex* je ax #1
    cmd_jne_r = 22,//Jumps on label if value in register NOT equals to zero. Ex* jne ax #1
    cmd_jl_r = 23,//Jumps on label if value in 1st reg is less then value in right. Ex* jl ax bx #2
    cmd_jg_r = 24,//Jumps on label if value in 1st reg is greater then value in right. Ex* jg ax bx #2
    cmd_call = 25,//Calls function from label. Ex* call #1
    cmd_ret = 26, //Returns from function. Ex* ret
    cmd_end = 27, //Shows, that end was reached. Ex* end 
};

enum registers {
    rax = 0,
    rbx = 1,
    rcx = 2,
    rdx = 3,
    rex = 4,
};

enum flags{
    f_con = 0,
    f_reg = 1,
};

int main(int argc, char* argv[])
{
    double *mem;
    int memleng = 0, ip = 0;
    char answ[MAX_SIZE];
    stack_s stack, call_stack;
    double reg[5] = {0,0,0,0,0}, temp = 0;    

    FILE *filein = NULL;
    filein = fopen(argv[1], "rt");

    if ((argc != 2) || (filein == NULL))
    {
        printf("./<programm name> <input file>\n");
        exit(1);
    }

    fread(&memleng, 1, sizeof(int), filein);

    printf("memleng is %d\n", memleng);
    
    mem = (double*)calloc(memleng, sizeof(double));
    fread(mem, memleng, sizeof(double), filein);

    ctor(&stack, 10, 5);
    ctor(&call_stack, 10, 1);

    for (ip = 0; ip < memleng; ip++)
        fprintf(stdout, "mem[%d] = %lg \n", ip, mem[ip]);
    printf("1\n");
    ip = 0;

    while ((ip < memleng) && (mem[ip] != cmd_end))
    {
        switch((int)mem[ip])
        {
            case cmd_push_c:
            push(&stack, mem[ip+1]);
            ip += 5;
            break;

            case cmd_push_r:
            push(&stack, reg[(int)mem[ip+1]]);
            ip += 5;
            break;

            case cmd_pop_c:
            pop(&stack);
            ip += 5;
            break;

            case cmd_pop_r:
            reg[(int)mem[ip+1]] = pop(&stack);
            ip += 5;
            break;

            case cmd_in:
            scanf("%lg", &temp);
            push(&stack, temp);
            ip += 5;
            break;

            case cmd_out:
            temp = pop(&stack);
            printf("%lg\n", temp);
            push(&stack, temp);
            ip += 5;
            break;

            case cmd_add_c:
            push(&stack, pop(&stack) + pop(&stack));
            ip += 5;
            break;

            case cmd_sub_c:
            push(&stack, -1*pop(&stack) + pop(&stack));
            ip += 5;
            break;

            case cmd_mul_c:
            push(&stack, pop(&stack) * pop(&stack));
            ip += 5;
            break;

            case cmd_div_c:
            push(&stack, 1/pop(&stack) * pop(&stack));
            ip += 5;
            break;

            case cmd_add_r:
            reg[(int)mem[ip+1]] = reg[(int)mem[ip+2]] + reg[(int)mem[ip+3]];
            ip += 5;
            break;

            case cmd_sub_r:
            reg[(int)mem[ip+1]] = reg[(int)mem[ip+2]] - reg[(int)mem[ip+3]];
            ip += 5;
            break;

            case cmd_mul_r:
            reg[(int)mem[ip+1]] = reg[(int)mem[ip+2]] * reg[(int)mem[ip+3]];
            ip += 5;
            break;

            case cmd_div_r:
            reg[(int)mem[ip+1]] = reg[(int)mem[ip+2]] / reg[(int)mem[ip+3]];
            ip += 5;
            break;

            case cmd_inc:
            reg[(int)mem[ip+1]] += 1;
            ip += 5;
            break;

            case cmd_dec:
            reg[(int)mem[ip+1]] -= 1;
            ip += 5;
            break;

            case cmd_mov_c:
            reg[(int)mem[ip+1]] = mem[ip+2];
            ip += 5;
            break;

            case cmd_mov_r:
            reg[(int)mem[ip+1]] = reg[(int)mem[ip+2]];
            ip += 5;
            break;

            case cmd_jmp:
            ip = (int)mem[ip+1];
            break;

            case cmd_je_r:
            if (reg[(int)mem[ip+1]] == 0)
                ip = (int)mem[ip+2];
            else
                ip += 5;
            break;

            case cmd_jne_r:
            if (reg[(int)mem[ip+1]] != 0)
                ip = (int)mem[ip+2];
            else
                ip += 5;
            break;

            case cmd_jl_r:
            if (reg[(int)mem[ip+1]] < reg[(int)mem[ip+2]])
                ip = (int)mem[ip+3];
            else
                ip +=5;
            break;

            case cmd_jg_r:
            if (reg[(int)mem[ip+1]] > reg[(int)mem[ip+2]])
                ip = (int)mem[ip+3];
            else
                ip +=5;
            break;

            case cmd_call:
                push(&call_stack, ip + 5);
                ip = (int)mem[ip+1];
            break;

            case cmd_ret:
                ip = (int)pop(&call_stack);
            break;

            case cmd_end:
            printf("End command have been reached. Something wrong happen.\n");
            break;

            default:
            fprintf(stdout, "Unknown command found/End coomand loosed/Label field met\nIn position %d\n", ip);
            fprintf(stdout, "Type Y to continue or any other letter to exit\n");
            fflush(stdin);
            fgets(answ, MAX_SIZE, stdin);
            if (answ[0] == 'Y')
            {
                printf("Answ is %s\n", answ);
                ip += 5;
                break;
            }
            else
            {   printf("Answ is %s\n", answ);
                exit(2);
                break;                
            }
        }
    printf("Ended switch, ip is now %d\n", ip);
    } 

    printf("Dump of stack:\n");
    dump(stack);
    printf("Dump of call_stack:\n");
    dump(call_stack);

    free (mem);

    dtor(&stack);
    dtor(&call_stack);
    
    fclose(filein);

    return 0;
}
