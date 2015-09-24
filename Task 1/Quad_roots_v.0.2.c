#include <stdio.h>
#include <math.h>

double Lin_root ( double b , double c ){

    double root;

    if ( ( b == 0 ) && ( c == 0 ) ) {
        printf("Quantity of roots are infinite");
    }
    else {
        if ( b == 0 ) {
            printf("No roots \n");
        }

        else {
            root = - c / b ;
            printf("%lg\n", root);

        };
    };
}

double Quad_root_hi ( double a , double b , double c) { //calculates a value of a higher root and returns its value if possible
     if ( Roots_count( a , b , c) >= 1 ) {
    double root =( - b + sqrt ( b * b - 4 * a *c) )/ ( 2 * a );
    return root ;
     }
     else {
        if ( Roots_count( a , b , c) == 0 ) {
                printf("No real roots");
            }
        else {
            printf("Expected quadratic equalization, met linear\n");
        }
     }
}

double Quad_root_low ( double a , double b , double c) { //calculates a value of a lower root and returns its value if possible
    if ( Roots_count( a , b , c) >= 1) {
        double root = ( - b - sqrt ( b * b - 4 * a *c) )/ ( 2 * a );
        return root ;
    }
    else {
        return ;
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

double Quadratic_roots_display ( double a , double b , double c) { //shows on display roots of equalization, if it has ones

    double Discriminant = ( b * b ) - (4 * a * c);

    if ( Roots_count( a , b , c) == 0 ) {
        printf("No real roots");
    };

    if ( Roots_count( a , b , c) == -1 ) {
        return Lin_root ( b , c );
    };

    if ( Roots_count( a , b , c) == 1 ) {
        printf("%g\n" ,- b / ( 2 * a));
    };

    if ( Roots_count( a , b , c) == 2 ) {
        printf("%g\n%g\n" , ( - b + sqrt ( Discriminant ) ) / ( 2 * a), ( - b - sqrt ( Discriminant ) ) / ( 2 * a) );
    };

    return 0;

}

int main() {
    double a , b , c ;
    int d;

    if ( ( d = scanf("%lg %lg %lg", &a,&b,&c) ) == 3 ) {
        Quadratic_roots_display ( a, b, c);
    }
    else {
        printf("Unexpected input data\n");
    }
    return 0;
}
