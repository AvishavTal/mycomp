#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "mycomp.h"
#include "command.h"

/**
 * print information about invalid input.
 * @param info the information to print
 */
void print_err(enum info info) {
    switch (info){
        case EOF_E:
            printf("end of file reached. next time insert the 'stop' command to exit.\n");
            break;
        case UNDEFINED_VAR:
            printf("Undefined variable name.\n");
            break;
        case UNDEFINED_COMMAND:
            printf("Undefined command.\n");
            break;
        case NOT_DOUBLE:
            printf("Invalid argument - not a number.\n");
            break;
        case MISSING_PARAM:
            printf("Missing parameter.\n");
            break;
        case EXTRA_TEXT:
            printf("Extraneous text after command.\n");
            break;
        case ILLEGAL_COMMA:
            printf("Illegal comma.\n");
            break;
        case MISSING_COMMA:
            printf("Missing comma.\n");
            break;
        default:
            printf("Something went wrong.");
    }
}

void run_calc(complex complex_array[]){
    enum info info;
    command command1;
    command1=init_command();
    printf("calculator is on. please insert a command.\n");
    while ((info= get_command(command1)) != EOF_E){
        if (info!=BLANk_LINE){
            if (info==OK){
                run_command(command1,complex_array);
                print_result(command1);
            } else {
                print_err(info);
            }
            printf("\nwaiting for command.\n");
        }
    }
    print_err(EOF_E);
    exit(0);
}

void init_comp_array(complex complex_array[]) {
    int i;
    for (i = 0; i < ARRAY_SIZE ; i++) {
        complex_array[i]= init_comp(0,0);
    }
}

int main(){
    complex complex_array[ARRAY_SIZE];
    init_comp_array(complex_array);
    run_calc(complex_array);
    return 0;
}

