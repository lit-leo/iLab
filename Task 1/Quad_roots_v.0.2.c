#include <stdio.h>
#include <math.h>

#define DISCRIMINANT(x,y,z) (y*y - 4*x*z)
#define HI_ROOT(a,b,c) ( -b + sqrt (DISCRIMINANT(a,b,c)) )/(2*a)
#define LO_ROOT(a,b,c) ( -b - sqrt (DISCRIMINANT(a,b,c)) )/(2*a)

struct root {
    double fir;
    double sec;
};

double Lin_root(double b ,double c );

struct root Quad_root(double a, double b, double c){
    struct root temp;
    temp.fir = 0;
    temp.sec = 0;

    if (Roots_count(a,b,c) == -1)
    {
        temp.fir = Lin_root(b,c);
        return temp;
    };
    if (Roots_count(a,b,c) == 0)
    {
        printf("No real roots.");
        return temp;
    };
    if (Roots_count(a,b,c) == 1)
    {
        temp.fir = HI_ROOT(a,b,c);
        temp.sec = HI_ROOT(a,b,c);
        return temp;
    };
    if (Roots_count(a,b,c) == 2)
    {
        temp.fir = HI_ROOT(a,b,c);
        temp.sec = LO_ROOT(a,b,c);
        return temp;
    };
};

double Lin_root(double b ,double c ){

    double root;

    if ( ( b == 0 ) && ( c == 0 ) ) {
        printf("Quantity of roots are infinite");
        return 0;
    }
    else {
        if ( b == 0 ) {
            printf("No roots \n");
            return 0;
        }

        else {
            root = - c / b ;
            printf("%lg\n", root);
            return root;
        }
    }
}

int Roots_count( double a , double b , double c) { //counts quantity of roots, return -1 if met linear equalization

    double Discriminant = ( b * b ) - (4 * a * c);

    if ( a == 0 ) {
        printf("Expected quadratic equalization, met linear\n");
        return -1;
    };

    if ( Discriminant < 0 ) {
        return 0;
    };


    if ( Discriminant == 0 ) {
        return 1;
    };

    if ( Discriminant > 0 ) {
        ; return 2;
    };
}

/*double Quadratic_roots_display ( double a , double b , double c) { //shows on display roots of equalization, if it has ones

    double Discriminant = ( b * b ) - (4 * a * c);

    if ( Roots_count( a , b , c) == -1 ) {
        return Lin_root ( b , c );
    };

    if ( Roots_count( a , b , c) == 0 ) {
        printf("No real roots");
    };

    if ( Roots_count( a , b , c) == 1 ) {
        printf("%g\n" ,- b / ( 2 * a));
    };

    if ( Roots_count( a , b , c) == 2 ) {
        printf("%g\n%g\n" , ( - b + sqrt ( Discriminant ) ) / ( 2 * a), ( - b - sqrt ( Discriminant ) ) / ( 2 * a) );
    };

    return 0;

}
*/
int main() {
    double a , b , c ;
    int d;

    if ( ( d = scanf("%lg %lg %lg", &a,&b,&c) ) == 3 ) {
        //Quadratic_roots_display(a,b,c);
        printf("\n%lg\n",Quad_root(a,b,c).fir);
        printf("\n%lg\n",Quad_root(a,b,c).sec);
    }
    else {
        printf("Unexpected input data\n");
    }
    return 0;
}
