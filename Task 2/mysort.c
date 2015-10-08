#include <stdio.h>
#include <time.h>
//#include <unistd.h>

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

void input( int* a ){
    int i;
    for ( i = 0 ; i <= 9999 ; i++){
        a[i] = 5 * i ;
    }
    }

void qsort( int* array , int first , int last){

    int i = first, j = last, base = array[(first + last) /2];
    out(array, first, last);
    printf("base [%d] = %d\n",(first + last) /2,base);
    while ( i <= (j-1) ) {
        printf("loop\n");
        while ((*( array + i ) < base) && ((i+1) < j)) i++;
        printf("move right done\n");
        while ((*(array + j) > base) && (i < (j-1))) j--;
        printf("move left done\n");
        printf("(i,j)=(%d,%d)\n", i, j);

        if ( i <= j ) {
            if (array[i] > array[j])
                grswp ( array + i , array + j);
            printf("swaped\n");
            out(array,first,last);
            if ((i+1) < (j-1))
            {
                i++;
                j--;
            }
            printf("(i,j)=(%d,%d)\n", i, j);
        }
    }
    out(array,first,last);
    printf("(i,j)=(%d,%d)\n", i, j);
    printf("done\n");
    printf("\n");
    printf("\n");
    printf("\n");

  /*  if ( j < last )
    {
        printf("call %d-%d\n",j,last);
        qsort(array, j , last);
    }
    if ( i > first )
    {
        printf("call %d-%d\n",first,i);
        qsort(array , first , i);
    } */
}
//virtualbox

int insort(int *Array, int ArraySize)
{
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
    int array[10000];
    int array2[10000];
    //printf("%lld\n",time(NULL));
    printf("%lld\n",time(NULL));
    input( array );
    input( array2 );
    out( array, 0,25 );
    clk0 = time(NULL);
    insort( array ,  25 );
    getchar();
    out( array, 0,9 );
    clk1 = time(NULL);
    qusort( array , 1 , 9);
    clk2 = time(NULL);
    out( array2, 0, 25 );
    printf("Time for InSort = %lld \n", clk1 - clk0);
    printf("Time for QuSort = %lld \n", clk2 - clk1);
    return 0;
    }
