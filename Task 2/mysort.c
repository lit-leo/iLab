#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 120000

void input( int* a ){
    int i = 0;

    srand(time(NULL)-98);
    for ( i = 0 ; i <= SIZE - 1 ; i++){
        a[i] = rand() ;
    }
    }

void out( int* a, int s, int e ){
    int i;
    for ( i = s ; i <= e ; i++ ) printf("%d ", *(a+i));
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

void swp( int* a , int* b ){
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void qusort(int *dArray, unsigned int iLeft, unsigned int iRight){
   unsigned long int iY, iJ;
   double dX;
   iY=iLeft-1;
   iJ=iRight+1;
   dX=dArray[iLeft];
   do {
      do {
         iJ--;
      } while(dArray[iJ]>dX);
      do {
         iY++;
      } while(dArray[iY]<dX);
      if (iY<iJ) {
         swp(&dArray[iY],&dArray[iJ]);
      }
   } while(iY<iJ);
   if (iJ+1<iRight) qusort(dArray, iJ+1, iRight);
   if (iLeft<iJ) qusort(dArray, iLeft, iJ);
}

void bsort( int* a , int leng ){
    int i , j;
    for ( i = 0 ; i <= leng ; i++){
        for ( j = i ; j <= leng ; j++)
            grswp( (a+i) , (a+j) );
    }
}

int insort(int *Array, int ArraySize){
   double dKey;
   int i, j;
   for(i=1; i<ArraySize; i++)
   {
      dKey=Array[i];
      j=i-1;
      while((j>=0)&&(Array[j]>dKey))
      {
         Array[j+1]=Array[j];
         j--;
      }
      Array[j+1]=dKey;
   }
   return 0;
}

int main() {

    long long int clk0 , clk1 , clk2;
    int array[SIZE], array2[SIZE];
    int i = 0;

    input(array);
    for (i = 0; i < SIZE ; i++)
        array2[i] = array[i];
    clk0 = time(NULL);
    insort( array2 ,  SIZE);
    clk1 = time(NULL);
    qusort( array , 1 , SIZE - 1);
    clk2 = time(NULL);
    printf("Time for InSort = %lg \n",difftime(clk1, clk0));
    printf("Time for QuSort = %lld \n",difftime(clk2, clk1));

    return 0;
    }
