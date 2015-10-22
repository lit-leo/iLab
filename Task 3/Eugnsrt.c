#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRLNG 90

int cmp(char *a,char *b);
void swp(char **a,char **b);
int qtystr(FILE *f);

int cmp(char *a,char *b)
{
	int i = 0;

	while ( (a[i] != '\0') && (b[i] != '\0') )
	{
		if (a[i] > b[i])
			return 1;
		if (a[i] < b[i])
			return -1;
		i++;
	}

    if ( (a[i] == '\0') && (b[i] != '\0') )
		return -1;
	if ( (a[i] != '\0') && (b[i] == '\0') )
		return 1;
	if ( (a[i] == '\0') && (b[i] == '\0') )
		return 0;
};

void swp(char **a,char **b)
{
	char *temp = NULL;

	temp = *a;
	*a = *b;
	*b = temp;
};

int qtystr(FILE *f)
{
    int leng = 0;
    char s[256];

    while (fgets( s , 256 , f) != NULL)
        {
            ++leng;
        };
    rewind(f);
    return leng;
}

int main()
{
    int i = 0 , j = 0, leng = 0;
    char buffer[STRLNG] = {}, filebuffer[64] = {}, filename[64] = {};
    char **storage = NULL;
    FILE *filein = NULL, *fileout = NULL;

    fgets(filebuffer, 64, stdin);
    strncpy(filename, filebuffer, strlen(filebuffer)-1);
    filein = fopen(filename, "rt");
    if (filein == NULL)
        return 1;

    *filename = "";

    fgets(filebuffer, 64, stdin);
    strncpy(filename, filebuffer, strlen(filebuffer)-1);
    fileout = fopen(filename, "wt");
    if (fileout == NULL)
        return 2;

    leng = qtystr(filein);

    storage = (char **)malloc(sizeof(char *) * leng);

    for ( i = 0 ; i < leng ; i++)
    {
        storage[i] = (char *)malloc(sizeof(char) * STRLNG);
        fgets( storage[i] , STRLNG , filein);
    }

	i = 0;
	j = 0;
	for (i = 0 ; i < leng ; i++)
	{
		for (j = i; j < leng ; j++)
		{
			if (cmp(storage[i], storage[j]) == 1)
				swp(&storage[i], &storage[j]);
		}
	}

	for ( i = 0 ; i < leng ; i++)
    {
		fputs( storage[i] , fileout);

    };

    fflush(fileout);
    fclose(filein);
    fclose(fileout);

    for ( i = 0 ; i < leng ; i++)
    {
        free(storage[i]);
    }
    free(storage);

    return 0;
}

