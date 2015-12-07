#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 32
#define READ fread(record, sizeof(double), 5, filein)

enum commands {
    lab = 0,        //Constant for a label
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
    cmd_label = 19,//Showes, that following expression is an adress. In .bin file it will be seen as: *null* *null* *null* *null*
    cmd_jmp = 20, //Jumps on label. Ex* jmp #1
    cmd_je_r = 21,//Jumps on label if value in register equals to zero. Ex* je ax #1
    cmd_jne_r = 22,//Jumps on label if value in register DOES NOT equal to zero. Ex* jne ax #1
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

int isNumber(char *string) // Returns 1 is string is a number and 0 if not
{
    int i = 0, flag = 0;

    for (i = 0; i < strlen(string); i++)
        {
            //printf("Checking symbol %d of string\n", i);
            if ((isdigit(string[i]) != 0) || (string[i] == '\n') || (string[i] == '-') || (string[i] == '.'))
                {
                    //printf("Condition passed on step %d\n", i);
                    flag = 1;
                }
            else
                return 0;
        }

    return flag;
}

char * regname(double reg) //Returns name of register if possible
{
    if ((reg < 0) || (reg > 5))
    {
        printf("Unvalid data met while analysing register\n");
        return "NULL";
    }
    else
    {    
        if ((int)(reg) == rax)
            return "ax";
        else
        if ((int)(reg) == rbx)
            return "bx";
        else
        if ((int)(reg) == rcx)
            return "cx";
        else
        if ((int)(reg) == rdx)
            return "dx";
        else
        if ((int)(reg) == rex)
           return "ex";
    }
}

int main(int argc, char* argv[])
{
    char buffer[MAX_SIZE], *cmd = NULL, answ[MAX_SIZE];
    int leng = 0, i = 0, j = 0, label[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    double value = 0;
    double record[5] = {0,0,0,0,0};

    FILE *filein = NULL, *fileout = NULL;
    filein = fopen(argv[1], "rt");
    fileout = fopen(argv[2], "wb");

    if ((argc != 3) || (filein == NULL) || (fileout == NULL))
    {
        printf("./<programm name> <input file> <output file>\n");
        exit(1);
    }
    
    fread(&leng, 1, sizeof(int), filein);
    leng /= 5;

    for (i = 0; i < leng; i++)
    {
        READ;

        switch((int)record[0])
        {
            case cmd_push_c:
            fprintf(fileout,"push %lg\n", record[1]);
            break;

            case cmd_push_r:
            fprintf(fileout,"push %s\n", regname(record[1]));
            break;

            case cmd_pop_c:
            fprintf(fileout,"pop\n");
            break;

            case cmd_pop_r:
            fprintf(fileout,"pop %s\n", regname(record[1]));
            break;

            case cmd_in:
            fprintf(fileout,"in\n");
            break;

            case cmd_out:
            fprintf(fileout,"out\n");
            break;

            case cmd_add_c:
            fprintf(fileout,"add\n");
            break;

            case cmd_sub_c:
            fprintf(fileout,"sub\n");
            break;

            case cmd_mul_c:
            fprintf(fileout,"mul\n");
            break;

            case cmd_div_c:
            fprintf(fileout,"div\n");
            break;

            case cmd_add_r:
            fprintf(fileout,"add %s %s %s\n", regname(record[1]), regname(record[2]), regname(record[3]));
            break;

            case cmd_sub_r:
            fprintf(fileout,"sub %s %s %s\n", regname(record[1]), regname(record[2]), regname(record[3]));
            break;

            case cmd_mul_r:
            fprintf(fileout,"mul %s %s %s\n", regname(record[1]), regname(record[2]), regname(record[3]));
            break;

            case cmd_div_r:
            fprintf(fileout,"div %s %s %s\n", regname(record[1]), regname(record[2]), regname(record[3]));
            break;

            case cmd_inc:
            fprintf(fileout,"inc %s\n", regname(record[1]));
            break;

            case cmd_dec:
            fprintf(fileout,"dec %s\n", regname(record[1]));
            break;

            case cmd_mov_c:
            fprintf(fileout,"mov %s %lg\n", regname(record[1]), record[2]);
            break;

            case cmd_mov_r:
            fprintf(fileout,"mov %s %s\n", regname(record[1]), regname(record[2]));
            break;

            case cmd_jmp:
            fprintf(fileout,"jmp #%lg\n", record[2]);
            break;

            case cmd_je_r:
            fprintf(fileout,"je %s #%lg\n", regname(record[1]), record[3]); 
            break;

            case cmd_jne_r:
            fprintf(fileout,"jne %s #%lg\n", regname(record[1]), record[3]); 
            break;

            case cmd_jl_r:
            fprintf(fileout,"jl %s %s #%lg\n", regname(record[1]), regname(record[2]), record[4]);
            break;

            case cmd_jg_r:
            fprintf(fileout,"jg %s %s #%lg\n", regname(record[1]), regname(record[2]), record[4]);
            break;

            case cmd_call:
            fprintf(fileout,"call #%lg\n", record[2]); 
            break;

            case cmd_ret:
            fprintf(fileout,"ret\n"); 
            break;

            case cmd_label:
            fprintf(fileout,"#%lg:\n", record[1]); 
            break;
            case cmd_end:
            fprintf(fileout,"end\n");
            break;

            default:
            fprintf(stdout, "Unknown command found\nIn line %d\n", i);
            fprintf(stdout, "Type Y to continue or any other letter to exit\n");
            fflush(stdin);
            fgets(answ, MAX_SIZE, stdin);
            if (answ[0] == 'Y')
                {
                    printf("Answ is %s\n", answ);
                    i += 1;
                    break;
                }
            else
            {   printf("Answ is %s\n", answ);
                exit(2);
                break;
            }
        }
    }

    fclose(filein);
    fclose(fileout);
    return 0;
}