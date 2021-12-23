


typedef struct complex *complex;

/*initial complex number*/
complex init_comp(double real, double img);


 /*get a complex number and change its rael and img to be the new real and img*/
 void read_comp(complex complex1,double new_real,double new_img);

/*get a complex number to print and print it*/
void print_comp(complex to_print);

/*get tow complex numbers and assign the result of adding them together to dest*/
void add_comp(complex dest, complex complex1, complex complex2);

/*get tow complex numbers and assign the result of subtraction from each other to dest*/
void sub_comp(complex dest, complex complex1, complex complex2);

/*get complex number and real number and return their multiplication result*/
void mult_comp_real(complex dest, complex complex1, double real);

/*get complex number and imaginary number and assign their multiplication result to dest*/
void mult_comp_img(complex dest, complex complex1, double img);

/*get tow complex numbers and assign their multiplication result to dest*/
void mult_comp_comp(complex dest, complex complex1, complex complex2);

/*get a complex number and assign its absolute value to dest*/
void abs_comp(complex dest, complex complex1);
