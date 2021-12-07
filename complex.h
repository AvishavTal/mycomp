typedef struct complex_struct{
    int real;
    int img;
}complex;

/*initial complex number*/
complex *read_com(int real,int img);

/*get a complex number to print and print it*/
void print_comp(complex to_print);

/*get tow complex numbers and return the result of adding them together*/
complex add_comp(complex complex1, complex complex2);

/*get tow complex numbers and return the result of subtraction from each other*/
complex sub_comp(complex complex1,complex complex2);

/*get complex number and real number and return their multiplication result*/
complex mult_comp_real(complex complex1,int real);

/*get complex number and imaginary number and return their multiplication result*/
complex mult_comp_img(complex complex1,int img);

/*get tow complex numbers and return their multiplication result*/
complex mult_comp_comp(complex complex1, complex complex2);

/*get a complex number and return its absolute value*/
