#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "mycomp.h"
#include "command.h"
#include "string_manipulations.h"

#define LINE_SIZE 1000
#define ARRAY_SIZE 6

int have_to_print_result(command cmd);

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

/**
 * manage the program
 * @param complex_array
 */
void run_calc(complex complex_array[]){
    enum info info;
    char line[LINE_SIZE];
    command command1;
    complex result;
    command1=init_command();
    printf("calculator is on. please insert a command.\n");
    while ((fgets(line,LINE_SIZE,stdin)!= NULL)){
        trim_whitespace(line);
        if (strlen(line)){
            printf("\n%s\n",line);
            info= set_command(command1,line);
            if (info==OK){
                run_command(command1,complex_array);
                result= get_result(command1);
                if (have_to_print_result(command1)){
                    print_comp(result);
                }
            } else {
                print_err(info);
            }
            printf("\nwaiting for command.\n");
        }
    }
    print_err(EOF_E);
    exit(0);
}

/**
 * @param cmd
 * @return return non zero iff cmd is a command the program have to print the result
 */
int have_to_print_result(command cmd) {
    char *action;
    action=get_action(cmd);
    return (!strcmp(action,"add_comp")||!strcmp(action,"sub_comp")||!strcmp(action,"mult_comp_real")||
            !strcmp(action,"mult_comp_img")||!strcmp(action,"mult_comp_comp")||!strcmp(action,"abs_comp"));
}

/**
 * initialize the array of complex variables
 * @param complex_array
 */
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