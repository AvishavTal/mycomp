//
// Created by avishav on 8.12.2021.
//
#include <stdio.h>
#include "complex.h"
void init_comp_test(){
    complex complex1;
    complex1= init_comp(1, 2);
}
void print_com_test(){
    complex real;
    complex only_img;
    complex pos_img;
    complex neg_img;
    real= init_comp(1, 0);
    only_img= init_comp(0, -1);
    pos_img= init_comp(1, 1);
    neg_img= init_comp(1, -1);
    printf("real:\t");
    print_comp(real);
    printf("only_img:\t");
    print_comp(only_img);
    printf("pos img:\t");
    print_comp(pos_img);
    printf("neg img:\t");
    print_comp(neg_img);
}

void add_comp_test(){
    complex complex1,complex2,result;
    complex1= init_comp(1,2);
    complex2= init_comp(4,5);
    result= add_comp(complex1,complex2);/* 5+7i */
    printf("\nadd comp :\n");
    printf("5+7i=\t");
    print_comp(result);
    complex1= init_comp(1,1);
    complex2= init_comp(-1,-1);
    result= add_comp(complex2,complex1);/*0*/
    printf("0=\t");
    print_comp(result);
}
int main(){
    init_comp_test();
    print_com_test();
    add_comp_test();
    return 0;
}
