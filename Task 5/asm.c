#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 32
#define WRT fwrite(record, sizeof(double), 5, fileout)

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
    cmd_label = 19,//Showes, that following expression is an adress. In .bin file it will be seen as: 19 <number of label> *null* *null* *null*
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

double regnum(char *cmd) //returns number of register, -1 if constant met, -2 if unvalid data.
{
    if (cmd == NULL)
    {
        printf("String to analyse does not exist. Check if commands are correct\n");
        return -2;
    }

    if(isNumber(cmd) == 1)
        return -1;
    else
        
        if ((strcmp(cmd,"ax") == 0) || (strcmp(cmd,"ax\n") == 0))
            return rax;
        else
        if ((strcmp(cmd,"bx") == 0) || (strcmp(cmd,"bx\n") == 0))
            return rbx;
        else
        if ((strcmp(cmd,"cx") == 0) || (strcmp(cmd,"cx\n") == 0))
            return rcx;
        else
        if ((strcmp(cmd,"dx") == 0) || (strcmp(cmd,"dx\n") == 0))
            return rdx;
        else
        if ((strcmp(cmd,"ex") == 0) || (strcmp(cmd,"ex\n") == 0))
            return rex;
        else
        {
            printf("Unvalid data met while analysing register\n");
            return -2;
        }
}

int qtystr(FILE *f)
{
    int leng = 0;
    char s[256];

    while (fgets( s , MAX_SIZE , f) != NULL)
        {
            ++leng;
        };
    rewind(f);
    return leng;
}

int main(int argc, char* argv[])
{
    char buffer[MAX_SIZE], *cmd = NULL;
    int leng = 0, i = 0, j = 0, label[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    double value = 0, flag = 0; 
    double record[5] = {0,0,0,0,0};

    FILE *filein = NULL, *fileout = NULL;
    filein = fopen(argv[1], "rt");
    fileout = fopen(argv[2], "wb");

    if ((argc != 3) || (filein == NULL) || (fileout == NULL))
    {
        printf("./<programm name> <input file> <output file>\n");
        exit(1);
    }

    leng = qtystr(filein);

    printf("leng is %d\n", leng);

    leng = leng * 5;

    printf("leng is %d\n", leng);
    fwrite(&leng, sizeof(int), 1, fileout); //First goes quantity of sizeof(double) blocks for cpu memory.
    leng = leng / 5;

    for (i = 0; i < leng; i++) //first check. Adding labels
    {
        fgets(buffer, MAX_SIZE, filein);
        if (buffer[0] == '#')
        {
            //printf("Met label in line %d\n", i+1);
            j = (buffer[1] - '0');
            label[j] = (i+1) * 4;
        }  
    }

    for (i = 0; i < 10; i ++)
        printf("%d ",label[i]);
    printf("\n");
    rewind(filein);

    for (i = 0; i < leng; i++) //second check. Adding commands
    {
        fgets(buffer, MAX_SIZE, filein);
        
        cmd = strtok(buffer, " ");
        printf("Met %s\n", cmd);
        
        if (cmd[0] == '#')
        {
            printf("Label %s met in line %d\n", cmd, i+1);
            record[0] = cmd_label;
            record[1] = cmd[1] - '0';
            WRT;
        }
        else  

        if (strcmp(cmd, "push") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);
            flag = regnum(cmd);
            if (flag <= -2) 
                printf("Error. Unexpected cmdand in line %d. Expected push.\n", i);
            else
                if(flag >= 0)
                {
                    record[0] = cmd_push_r;
                    record[1] = flag;
                    WRT;
                }
                else
                {
                    printf("Met something like %s\n", cmd);
                    printf("isNumber(cmd) = %d\n", isNumber(cmd));
                        {
                            value = atof(cmd);
                            printf("When atofed, it became %lg\n", value);
                            record[0] = cmd_push_c;
                            record[1] = value;
                            WRT;
                        }

                }
        }
        else 

        if (strcmp(cmd, "pop") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);
            flag = regnum(cmd);
            if (flag <0)
                printf("Error. Unexpected cmdand in line %d. Expected *pop register*.\n", i);
            else
            {
                record[0] = cmd_pop_r;
                record[1] = flag;
                WRT;
            }
        }
        else

        if (strcmp(cmd, "pop\n") == 0)
        {
            record[0] = cmd_pop_c;
            WRT;
        }
        else

        if (strcmp(cmd, "in\n") == 0)
        {
            record[0] = cmd_in;
            WRT;
        }
        else

        if (strcmp(cmd, "out\n") == 0)
        {
            record[0] = cmd_out;
            WRT;
        }
        else

        if (strcmp(cmd, "add\n") == 0)
        {
            record[0] = cmd_add_c;
            WRT;
        }
        else
        
        if (strcmp(cmd, "sub\n") == 0)
        {
            record[0] = cmd_sub_c;
            WRT;
        }
        else

        if (strcmp(cmd, "mul\n") == 0)
        {
            record[0] = cmd_mul_c;
            WRT;
        }
        else

        if (strcmp(cmd, "div\n") == 0)
        {
            record[0] = cmd_div_c;
            WRT;
        }
        else

        if (strcmp(cmd, "add") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected add.\n", i+1);
            else
            {
                flag = regnum(cmd);
                if (flag < 0)
                    printf("Invalid command in line %d. Expected add with registers.\n", i+1);
                else
                {
                    record[0] = cmd_add_r;
                    record[1] = regnum(cmd);
                    for (j = 0 ; j < 2; j++)
                    {
                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);
                    if (regnum(cmd) < 0)
                        printf("Error. Unexpected command in line %d. Expected add with registers.\n", i+1);
                    else
                        record[j+2] = regnum(cmd);
                    }
                    WRT;
                }

            }
        }
        else

        if (strcmp(cmd, "sub") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected sub with registers.\n", i+1);
            else
            {
                flag = regnum(cmd);
                if (flag < 0)
                    printf("Invalid command in line %d. Expected sub with registers.\n", i+1);
                else
                {
                    record[0] = cmd_sub_r;
                    record[1] = regnum(cmd);
                    for (j = 0 ; j < 2; j++)
                    {
                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);
                    if (regnum(cmd) < 0)
                        printf("Error. Unexpected command in line %d. Expected sub.\n", i+1);
                    else
                        record[j+2] = regnum(cmd);
                    }
                    WRT;
                }

            }
        }
        else

        if (strcmp(cmd, "mul") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected mul.\n", i+1);
            else
            {
                flag = regnum(cmd);
                if (flag < 0)
                    printf("Invalid command in line %d. Expected mul with registers.\n", i+1);
                else
                {
                    record[0] = cmd_mul_r;
                    record[1] = regnum(cmd);
                    for (j = 0 ; j < 2; j++)
                    {
                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);
                    if (regnum(cmd) < 0)
                        printf("Error. Unexpected command in line %d. Expected mul.\n", i+1);
                    else
                        record[j+2] = regnum(cmd);
                    }
                    WRT;
                }

            }
        }
        else

        if (strcmp(cmd, "div") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected div.\n", i+1);
            else
            {
                flag = regnum(cmd);
                if (flag < 0)
                    printf("Invalid command in line %d. Expected div\n", i+1);
                else
                {
                    record[0] = cmd_div_r;
                    record[1] = flag;
                    for (j = 0 ; j < 2; j++)
                    {
                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);
                    if (regnum(cmd) < 0)
                        printf("Error. Unexpected command in line %d. Expected div.\n", i+1);
                    else
                        record[j+2] = regnum(cmd);
                    }
                    WRT;
                }

            }
        }
        else

        if (strcmp(cmd, "inc") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected inc.\n", i+1);
            else
            {
                flag = regnum(cmd);

                if (flag <0)
                    printf("Invalid command in line %d. Expected inc\n", i+1);
                else
                {
                    record[0] = cmd_inc;
                    record[1] = flag;
                    WRT;
                }
            }
        }
        else

        if (strcmp(cmd, "dec") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected inc.\n", i+1);
            else
            {
                flag = regnum(cmd);

                if (flag <0)
                    printf("Invalid command in line %d. Expected dec\n", i+1);
                else
                {
                    record[0] = cmd_dec;
                    record[1] = flag;
                    WRT;
                }
            }
        }
        else

        if (strcmp(cmd, "mov") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected mov.\n", i+1);
            else
            {
                flag = regnum(cmd);

                if (flag < 0)
                    printf("Invalid command in line %d. Expected mov\n", i+1);
                else
                {
                    record[1] = flag;

                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);

                    flag = regnum(cmd);

                    if (flag <= -2)
                        printf("Unexpected command met in line %d. Expected mov\n", i+1);
                    else
                    if(flag == -1)
                    {
                        record[0] = cmd_mov_c;
                        record[2] = atof(cmd);
                        WRT;

                    }
                    else
                    {
                        record[0] = cmd_mov_r;
                        record[2] = flag;
                        WRT;
                    }
                }
            }
        }
        else

        if (strcmp(cmd, "jmp") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);
            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected jmp.\n", i+1);
            else
            if ((strlen(cmd) == 3) && (cmd[0] == '#') && (isdigit(cmd[1]) != 0))
            {
                record[0] = cmd_jmp;
                j = (cmd[1] - '0');
                record[1] = label[j];
                record[2] = j;
                WRT;
            }
            else
            {
                printf("Error (not null). Unexpected command in line %d. Expected jmp.\n", i+1);
            }        
        }
        else

        if (strcmp(cmd, "je") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);
            flag = regnum(cmd);
            if (flag < 0)
                printf("Error. Unexpected command in line %d. Expected je.\n", i+1);
            else
            {
                cmd = strtok(NULL, " ");
                printf("Met %s\n", cmd);

                if ((cmd != NULL) && (strlen(cmd) == 3) && (cmd[0] == '#') && (isdigit(cmd[1]) != 0))
            {
                record[0] = cmd_je_r;
                record[1] = flag;
                j = (cmd[1] - '0');
                record[2] = label[j];
                record[3] = j;
                WRT;
            }
            else
                printf("Error. Unexpected command in line %d. Expected je.\n", i+1); 
            }
        }
        else

        if (strcmp(cmd, "jne") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);
            flag = regnum(cmd);
            if (flag < 0)
                printf("Error. Unexpected command in line %d. Expected jne.\n", i+1);
            else
            {
                cmd = strtok(NULL, " ");
                printf("Met %s\n", cmd);

                if ((cmd != NULL) && (strlen(cmd) == 3) && (cmd[0] == '#') && (isdigit(cmd[1]) != 0))
            {
                record[0] = cmd_jne_r;
                record[1] = flag;
                j = (cmd[1] - '0');
                record[2] = label[j];
                record[3] = j;
                WRT;
            }
            else
                printf("Error. Unexpected command in line %d. Expected jne.\n", i+1); 
            }
        }
        else

        if (strcmp(cmd, "jl") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected jl.\n", i+1);
            else
            {
                flag = regnum(cmd);
                if (flag < 0)
                    printf("Invalid command in line %d. Expected jl\n", i+1);
                else
                {
                    record[0] = cmd_jl_r;
                    record[1] = flag;

                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);
                    flag = regnum(cmd);
                    if (flag < 0)
                        printf("Error. Unexpected command in line %d. Expected jl.\n", i+1);
                    else
                        record[2] = flag;
                    
                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);

                    if ((strlen(cmd) == 3) && (cmd[0] == '#') && (isdigit(cmd[1]) != 0))
                    {
                        j = (cmd[1] - '0');
                        record[3] = label[j];
                        record[4] = j;
                        WRT;
                    }
                    else
                        printf("Error. Unexpected command in line %d. Expected jl.\n", i+1);
                }

            }
        }
        else

        if (strcmp(cmd, "jg") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);

            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected jg.\n", i+1);
            else
            {
                flag = regnum(cmd);
                if (flag < 0)
                    printf("Invalid command in line %d. Expected jg\n", i+1);
                else
                {
                    record[0] = cmd_jg_r;
                    record[1] = flag;

                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);
                    flag = regnum(cmd);
                    if (flag < 0)
                        printf("Error. Unexpected command in line %d. Expected jg.\n", i+1);
                    else
                        record[2] = flag;
                    
                    cmd = strtok(NULL, " ");
                    printf("Met %s\n", cmd);

                    if ((strlen(cmd) == 3) && (cmd[0] == '#') && (isdigit(cmd[1]) != 0))
                    {
                        j = (cmd[1] - '0');
                        record[3] = label[j];
                        record[4] = j;
                        WRT;
                    }
                    else
                        printf("Error. Unexpected command in line %d. Expected jg.\n", i+1);
                }

            }
        }
        else

        if (strcmp(cmd, "call") == 0)
        {
            cmd = strtok(NULL, " ");
            printf("Met %s\n", cmd);
            if (cmd == NULL)
                printf("Error. Unexpected command in line %d. Expected call.\n", i+1);
            else
            if ((strlen(cmd) == 3) && (cmd[0] == '#') && (isdigit(cmd[1]) != 0))
            {
                record[0] = cmd_call;
                j = (cmd[1] - '0');
                record[1] = label[j];
                record[2] = j;
                WRT;
            }
            else
            {
                printf("Error (not null). Unexpected command in line %d. Expected call.\n", i+1);
            }        
        }
        else

        if ((strcmp(cmd, "ret\n") == 0) || (strcmp(cmd, "ret") == 0))
        {
            record[0] = cmd_ret;
            WRT;
        }
        else

        if ((strcmp(cmd, "end\n") == 0) || (strcmp(cmd, "end") == 0))
        {
            record[0] = cmd_end;
            WRT;
        }
        else
        {
            printf("Met unexpected command in line %d. Check the correctness.\n", i+1);
        }

    printf("Got out from cycle\n");
    record[0] = 0;
    record[1] = 0;
    record[2] = 0;
    record[3] = 0;
    record[4] = 0;
    j = 0;
    }
    fclose(filein);
    fclose(fileout);
    return 0;
}
