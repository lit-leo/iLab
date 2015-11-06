#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 32

int defwrd(char* comm)
{
    int flag = 0;

    if (strcmp(comm,"push") == 0)
        flag = 1;
    if (strcmp(comm,"pop\n") == 0)
        flag = 2;
    if (strcmp(comm,"add\n") == 0)
        flag = 3;
    if (strcmp(comm,"diff\n") == 0)
        flag = 4;
    if (strcmp(comm,"mul\n") == 0)
        flag = 5;
    if (strcmp(comm,"div\n") == 0)
        flag = 6;
    if (((strcmp(comm,"end\n") == 0) || (strcmp(comm,"end") == 0)))
        {
            flag = 7;
        }

    return flag;
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
    char buffer[MAX_SIZE], *comm = NULL;
    int flag = 0, leng = 0, i = 0;
    double value = 0;  

    FILE *filein = NULL, *fileout = NULL;
    filein = fopen(argv[1], "rt");
    fileout = fopen(argv[2], "w");

    if ((argc != 3) || (filein == NULL) || (fileout == NULL))
    {
        printf("./<programm name> <input file> <output file>\n");
        exit(1);
    }

    leng = qtystr(filein);

    for (i = 0; i < leng; i++)
    {
        fgets(buffer, MAX_SIZE, filein);
        comm = strtok(buffer, " ");

        flag = defwrd(comm);
        switch (flag)
        {
            case 1:
            fprintf(fileout, "%lg ", 1.0);
            comm = strtok(NULL, " ");
            value = atof(comm);
            fprintf(fileout, "%lg ", value);            
            break;

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            fprintf(fileout, "%lg ", (double)flag);
            break;

            default:
            printf("Unknown command found in line  %d\n", i+1);
            //exit(1);
            break;
        }
    }
    fclose(filein);
    fclose(fileout);
    return 0;
}
    
