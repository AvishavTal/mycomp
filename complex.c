
#include <stdlib.h>
#include <stdio.h>
#include "complex.h"
struct complex{
    float real;
    float img;
};

/*initial complex number*/
complex read_com(float real, float img){
    complex result;
    result=(complex) malloc(sizeof (struct complex));
    result->real=real;
    result->img=img;
    return result;
}

/*get a complex number to print and print it*/
void print_comp(complex to_print){
    printf("%f",to_print->real);
    if (to_print->img!=0){
        if (to_print->img>0){
            printf("%c",'+');
        }
        printf("%fi",to_print->img);
    }
    printf("\n");
}

/*get tow complex numbers and return the result of adding them together*/
complex add_comp(complex complex1, complex complex2);

/*get tow complex numbers and return the result of subtraction from each other*/
complex sub_comp(complex complex1,complex complex2);

/*get complex number and real number and return their multiplication result*/
complex mult_comp_real(complex complex1, float real);

/*get complex number and imaginary number and return their multiplication result*/
complex mult_comp_img(complex complex1, float img);

/*get tow complex numbers and return their multiplication result*/
complex mult_comp_comp(complex complex1, complex complex2);

/*get a complex number and return its absolute value*/
float abs_comp(complex complex1);