#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRQTY 806
#define STRLNG 90

int cmp(char *a,char *b);
void swp(char **a,char **b);


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


int main()
{
    int i = 0 , j = 0;
    char buffer[STRLNG] = {};
    char **storage = NULL;

    storage = (char **)malloc(sizeof(char *) * STRQTY);

    for ( i = 0 ; i < STRQTY ; i++)
    {
        storage[i] = (char *)malloc(sizeof(char) * STRLNG);
        fgets( storage[i] , STRLNG , stdin);
		//fputs( storage[i] , stdout);
    }

	i = 0;
	j = 0;
	for (i = 0 ; i < STRQTY ; i++)
	{
		for (j = i; j < STRQTY ; j++)
		{
			if (cmp(storage[i], storage[j]) == 1)
				swp(&storage[i], &storage[j]);
		}
	}

	for ( i = 0 ; i < STRQTY ; i++)
    {
		fputs( storage[i] , stdout);
    };

    for ( i = 0 ; i < STRQTY ; i++)
    {
        free(storage[i]);
    }
    free(storage);

    return 0;
}
