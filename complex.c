
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "complex.h"
struct complex{
    float real;
    float img;
};

/*initial complex number*/
complex init_comp(float real, float img){
    complex result;
    result=(complex) malloc(sizeof (struct complex));
    result->real=real;
    result->img=img;
    return result;
}

/*print the imaginary part of a complex number*/
void print_img(float img) {
    if (img==1){
        printf("i");
    } else if(img==-1){
        printf("-i");
    } else{
        printf("%fi",img);

    }
}

/*get a complex number to print and print it*/
void print_comp(complex to_print){
    if (!to_print->real && to_print->img){
        print_img(to_print->img);
    } else{
        to_print->real=to_print->real+0.0;/*convert negative 0 to positive.*/
        printf("%f",to_print->real);
        if (to_print->img){
            if (to_print->img>0){
                printf("%c",'+');
            }
            print_img(to_print->img);
        }
    }

    printf("\n");
}


/*get tow complex numbers and return the result of adding them together*/
complex add_comp(complex complex1, complex complex2){
    complex result;
    result= init_comp(0, 0);
    result->real=complex1->real+complex2->real;
    result->img=complex1->img+complex2->img;
    return result;
}

/*get tow complex numbers and return the result of subtraction from each other*/
complex sub_comp(complex complex1,complex complex2){
    complex result;
    result= init_comp(0,0);
    result->real=complex1->real-complex2->real;
    result->img=complex1->img-complex2->img;
    return result;
}

/*get complex number and real number and return their multiplication result*/
complex mult_comp_real(complex complex1, float real){
    complex result;
    result = init_comp(0,0);
    result->real=complex1->real*real;
    result->img=complex1->img*real;
    return result;
}

/*get complex number and imaginary number and return their multiplication result*/
complex mult_comp_img(complex complex1, float img){
    float real,result_img;
    real=img*complex1->img;
    result_img=img*complex1->real;
    return init_comp(real,result_img);
}

/*get tow complex numbers and return their multiplication result*/
complex mult_comp_comp(complex complex1, complex complex2){
    complex result;
    float real,img;
    real=complex1->real*complex2->real - complex1->img*complex2->img;
    img=complex1->real*complex2->img+complex1->img*complex2->real;
    return init_comp(real,img);
}

/*get a complex number and return its absolute value*/
float abs_comp(complex complex1){
    return sqrt(pow(complex1->real,2)+ pow(complex1->img,2));
}