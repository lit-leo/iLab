#include <stdio.h>

void out( int* a ){
    int i;
    for ( i = 0 ; i <= 9 ; i++ ) printf("%d", *(a+i));
    printf("\n");
    }

void grswp( int* a , int* b ){
    int temp;
    if ( *a > *b ) {
        temp = *b;
        *b = *a;
        *a = temp;
    }
}


void bsort( int* a , int leng ){
    int i , j;
    for ( i = 0 ; i <= leng ; i++){
        for ( j = i ; j <= leng ; j++)
            grswp( (a+i) , (a+j) );
    }
}

void input( int* a ){
    int i;
    for ( i = 0 ; i <= 9 ; i++){
        scanf("%d", (a+i) );
    }
    }

int main() {
    int array[10];
    input( array );
    out( array );
    bsort( array , 9 );
    out( array );
    return 0;
    }
