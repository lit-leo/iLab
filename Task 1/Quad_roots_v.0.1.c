#include <stdio.h>
#include <math.h>

double Lin_root ( double b , double c ){

    double root;

    if ( !b * !c ) {
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

double Quad_root_hi ( double a , double b , double c) { //calculates a value of a higher root
    double root =( - b + sqrt ( b * b - 4 * a *c) )/ ( 2 * a );
    return root ;
}

double Quad_root_low ( double a , double b , double c) { //calculates a value of a lower root
    if ( Roots_corectness_chk( a , b , c) >= 1) {
        double root = ( - b - sqrt ( b * b - 4 * a *c) )/ ( 2 * a );
        return root ;
    }
    else {
        return ;
    }
}

int Roots_corectness_chk( double a , double b , double c) { //checks if the equalization is correct and quadratic

    double Discriminant = ( b * b ) - (4 * a * c);

    if ( a == 0 ) {
        printf("Expected quadratic equalization, met linear\n");
        return 1;
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

    if ( Discriminant < 0 ) {
        printf("No real roots");
    };

    if ( a == 0 ) {
        return Lin_root ( b , c );
    };

    if ( Discriminant == 0 ) {
        printf("%g\n" ,- b / ( 2 * a));
    };

    if ( Discriminant > 0 ) {
        printf("%g\n%g\n" , ( - b + sqrt ( Discriminant ) ) / ( 2 * a), ( - b - sqrt ( Discriminant ) ) / ( 2 * a) );
    };

    return 0;

}

int main() {
    double a , b , c , d;
    scanf("%lg %lg %lg", &a,&b,&c);
    if( Roots_corectness_chk( a , b , c) != -1)
        {
        Quadratic_roots_display ( a, b, c);
        }
    return 0;
}
