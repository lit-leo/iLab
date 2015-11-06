#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 32


int main(int argc, char* argv[])
{
    char buffer[MAX_SIZE], *comm = NULL;
    int arg = 0, leng = 0, i = 0;
    double value = 0;  

    FILE *filein = NULL, *fileout = NULL;
    filein = fopen(argv[1], "rt");
    fileout = fopen(argv[2], "w");

    if ((argc != 3) || (filein == NULL) || (fileout == NULL))
    {
        printf("./<programm name> <input file> <output file>\n");
        exit(1);
    }
    
    do
    {
        fscanf(filein, "%d", &arg);

        switch (arg)
        {
            case 1:
            fprintf(fileout, "push ");
            fscanf(filein, "%lg", &value);
            fprintf(fileout, "%lg ", value);
            fprintf(fileout, "\n");
            break;

            case 2:
            fprintf(fileout, "pop\n");
            break;

            case 3:
            fprintf(fileout, "add\n");
            break;

            case 4:
            fprintf(fileout, "diff\n");
            break;

            case 5:
            fprintf(fileout, "mul\n");
            break;

            case 6:
            fprintf(fileout, "div\n");
            break;

            case 7:
            fprintf(fileout, "end");
            break;

            default:
            printf("Unknown command found in position  %d\n", i+1);
            //exit(1);
            break;
        }
    } while (arg != 7);
    fclose(filein);
    fclose(fileout);
    return 0;
}
    
