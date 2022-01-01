
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "complex.h"

/*
 * struct represent a complex number
 */
struct complex{
    double real;
    double img;
};

/*initial complex number*/
complex init_comp(double real, double img){
    complex result;
    result=(complex) malloc(sizeof (struct complex));
    result->real=real;
    result->img=img;
    return result;
}

/*get a complex number and change its rael and img_arg to be the new real_arg and img_arg*/
void read_comp(complex complex1,double new_real,double new_img){
    complex1->real=new_real;
    complex1->img=new_img;
}

/*print the imaginary part of a complex number*/
void print_img(double img) {
    if (img==1){
        printf("i");
    } else if(img==-1){
        printf("-i");
    } else{
        printf("%.2fi",img);
    }
}

/*get a complex number to print and print it*/
void print_comp(complex to_print){
    if (!to_print->real && to_print->img){
        print_img(to_print->img);
    } else{
        to_print->real=to_print->real+0.0;/*convert negative 0 to positive.*/
        printf("%.2f",to_print->real);
        if (to_print->img){
            if (to_print->img>0){
                printf("%c",'+');
            }
            print_img(to_print->img);
        }
    }
    printf("\n");
}


/*get tow complex numbers and assign the result of adding them together to dest*/
void add_comp(complex dest, complex complex1, complex complex2) {
    dest->real=complex1->real+complex2->real;
    dest->img=complex1->img+complex2->img;
}

/*get tow complex numbers and assign the result of subtraction from each other to dest*/
void sub_comp(complex dest, complex complex1, complex complex2) {
    dest->real=complex1->real-complex2->real;
    dest->img=complex1->img-complex2->img;
}

/*get complex number and real_arg number and assign their multiplication result to dest*/
void mult_comp_real(complex dest, complex complex1, double real) {
    dest->real=complex1->real*real;
    dest->img=complex1->img*real;
}

/*get complex number and imaginary number and assign their multiplication result to dest*/
void mult_comp_img(complex dest, complex complex1, double img) {
    dest->real=img*complex1->img;
    dest->img=img*complex1->real;
}

/*get tow complex numbers and assign their multiplication result to dest*/
void mult_comp_comp(complex dest, complex complex1, complex complex2) {
    dest->real=complex1->real*complex2->real - complex1->img*complex2->img;
    dest->img=complex1->real*complex2->img+complex1->img*complex2->real;
}

/*get a complex number and assign its absolute value to dest*/
void abs_comp(complex dest, complex complex1) {
    dest->real= sqrt(pow(complex1->real,2)+ pow(complex1->img,2));
    dest->img=0;
}