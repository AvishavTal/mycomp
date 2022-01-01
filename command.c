#include "command.h"
#include <ctype.h>
#include <string.h>
#include "string_manipulations.h"
#include "mycomp.h"

#define SEPARATOR ','

/**
 * an object that holds the user command
 */
struct cmd{
    char *action;   /*the action the command have to do.*/
    complex result; /*hold the result of the command.*/

    /*arguments for the command.*/
    int complex_arg1_pos;
    int complex_arg2_pos;
    double real_arg;
    double img_arg;
};

enum info set_action(command cmd, char *op);

enum info set_unary_param(command cmd, char **parameters, int parameters_len);

enum info set_bin_op_params(command cmd, char **parameters, int parameters_len);

enum info set_read_params(command cmd, char **parameters, int parameters_len);

enum info set_params(command cmd, char **parameters, int parameters_len);

enum info check_commas(char line[]);

int pick_complex_var(char *name, enum info *info);

enum info set_real(command cmd, char *real_str);

enum info set_img(command cmd, char *img_str);

int is_unary_op(char *action);

int op_with_const(char *action);

enum info set_const_arg(command cmd, char *str);

/**
 * set the command to be the user command
 * @param cmd the command to be modified
 * @param op the user command
 * @return OK if the calculator support the user command, UNDEFINED_COMMAND otherwise
 */
enum info set_action(command cmd, char *op) {
    enum info result;
    if (strcmp(op,"stop")==0||strcmp(op,"print_comp")==0||strcmp(op,"read_comp")==0||strcmp(op,"add_comp")==0||
        strcmp(op,"sub_comp")==0||strcmp(op,"mult_comp_real")==0||strcmp(op,"mult_comp_img")==0||
        strcmp(op,"mult_comp_comp")==0||strcmp(op,"abs_comp")==0){
        cmd->action = op;
        result= OK;
    } else{
        result=UNDEFINED_COMMAND;
    }
    return result;
}

/*assign the fildes of the given command according to the input from the user.
 * cm - the pointer of the command to be assigned.*/
enum info set_command(command cm, char *line) {
    enum info info;
    info = check_commas(line);
    if (info == OK){
        char *op;
        char **parameters;
        int parameters_len, op_len;
        op = strtok(line," \t");
        op_len=strlen(op);
        trim_whitespace(op);
        info = set_action(cm, op);
        if (info == OK){
            parameters=(char **)malloc(sizeof(char *));
            parameters_len = split(line + op_len+1, parameters, ", \t");
            info = set_params(cm, parameters, parameters_len);
            free(parameters);
        }
    }
    return info;
}

/*run the given command.*/
void run_command(command cm, complex complex_array[]) {
    char *name;
    name=cm->action;
    if (strcmp(name,"stop")==0) {
        exit(0);
    } else if (strcmp(name,"read_comp")==0){
        read_comp(complex_array[cm->complex_arg1_pos], cm->real_arg, cm->img_arg);
    } else if (strcmp(name,"print_comp")==0){
        print_comp(complex_array[cm->complex_arg1_pos]);
    } else if (strcmp(name,"add_comp")==0){
        add_comp(cm->result, complex_array[cm->complex_arg1_pos], complex_array[cm->complex_arg2_pos]);
    } else if (strcmp(name,"sub_comp")==0){
        sub_comp(cm->result, complex_array[cm->complex_arg1_pos], complex_array[cm->complex_arg2_pos]);
    } else if (strcmp(name,"mult_comp_real")==0){
        mult_comp_real(cm->result, complex_array[cm->complex_arg1_pos], cm->real_arg);
    } else if(strcmp(name,"mult_comp_img")==0){
        mult_comp_img(cm->result, complex_array[cm->complex_arg1_pos], cm->img_arg);
    } else if (strcmp(name,"mult_comp_comp")==0){
        mult_comp_comp(cm->result, complex_array[cm->complex_arg1_pos], complex_array[cm->complex_arg2_pos]);
    } else if(strcmp(name,"abs_comp")==0){
        abs_comp(cm->result,complex_array[cm->complex_arg1_pos]);
    }
}

/**
 * @param command1
 * @return the result of the given command
 */
complex get_result(command command1){
    return command1->result;
}

/**
 * @param cm
 * @return the action name of the command.
 */
char *get_action(command cm){
    return cm->action;
}

/**
 * @return  a new command
 */
command init_command() {
    command cmd;
    cmd=(command)malloc(sizeof(command));
    cmd->result= init_comp(0,0);
    return cmd;
}

/**
 * @param name the wanted complex variable
 * @param info the information about user input. if the wanted variable dose not exsits, info will be changed to UNDEFINED_VAR
 * @return index of the wanted variable if exists.
 */
int pick_complex_var(char *name, enum info *info) {
    int res;
    if (!strcmp(name, "A")){
        res = A_IDX;
    } else    if (!strcmp(name, "B")) {
        res=B_IDX;
    }
    else if (!strcmp(name, "C")) {
        res = C_IDX;
    }
    else if (!strcmp(name, "D")) {
        res = D_IDX;
    }
    else if (!strcmp(name, "E")) {
        res = E_IDX;
    }
    else if (!strcmp(name, "F")) {
        res = F_IDX;
    } else{
        *info=UNDEFINED_VAR;
    }
    return res;
}

/**
 * set the arguments command
 * @param cmd the command object that hold the information
 * @param parameters the input from user
 * @param parameters_len
 * @param complex_array the set that exists in the program
 * @return OK if the input is ok, detailed information otherwise
 */
enum info set_params(command cmd, char **parameters, int parameters_len) {
    enum info result=OK;
    if (!strcmp(cmd->action, "stop")) {
        if (parameters_len != 0) {
            result= EXTRA_TEXT;
        }
    } else if (is_unary_op(cmd->action)){
        result= set_unary_param(cmd, parameters, parameters_len);
    } else if (!strcmp(cmd->action, "read_comp")){
        result= set_read_params(cmd, parameters, parameters_len);
    }
    else {
        result= set_bin_op_params(cmd, parameters, parameters_len);
    }
    return result;
}

/**
 * set a constant argument of a command
 * @param cmd the command to set
 * @param str a string represent a floating point number.
 * @return information about the input.
 */
enum info set_const_arg(command cmd, char *str) {
    enum info result=OK;
    if (!strcmp(cmd->action,"mult_comp_real")){
        result=set_real(cmd,str);
    } else{
        result= set_img(cmd,str);
    }
    return result;
}

/**
 * @param action
 * @return 0 iff the action dose not suport a constant argument.
 */
int op_with_const(char *action) {
    return !strcmp(action,"mult_comp_real")|| !strcmp(action,"mult_comp_img");
}

/**
 * @param action
 * @return non zero iff the action act on one variable.
 */
int is_unary_op(char *action) {
    return !strcmp(action,"print_comp")|| !strcmp(action,"abs_comp");
}

/**
 * set the parameters to the read comp command
 * @param cmd the command to set
 * @param parameters array of parameters for the command
 * @param parameters_len the length of the array
 * @return detailed information about the validity of the input
 */
enum info set_read_params(command cmd, char **parameters, int parameters_len) {
    enum info result=OK;
    if (parameters_len<3){
        result= MISSING_PARAM;
    } else if(parameters_len>3){
        result=EXTRA_TEXT;
    }
    cmd->complex_arg1_pos = pick_complex_var(parameters[0], &result);
    if (result==OK){
        result = set_real(cmd,parameters[1]);
        if (result==OK){
            result=set_img(cmd,parameters[2]);
        }
    }
    return result;
}

/**
 * set the img_arg field of a command
 * @param cmd the command to set
 * @param img_str string represent a real_arg number
 * @return detailed information about the validity of the input
 */
enum info set_img(command cmd, char *img_str) {
    enum info result=OK;
    int is_double= str_to_double(img_str,&cmd->img_arg);
    if (!is_double){
        result=NOT_DOUBLE;
    }
    return result;
}

/**
 * set the real_arg field of a command
 * @param cmd the command to set
 * @param real_str string represent a real_arg number
 * @return detailed information about the validity of the input
 */
enum info set_real(command cmd, char *real_str) {
    enum info result=OK;
    int is_double= str_to_double(real_str,&cmd->real_arg);
    if (!is_double){
        result=NOT_DOUBLE;
    }
    return result;
}

/**
 * set the arguments of  commands that takes tow set and put the result in third
 * @param cmd the command object that hold the information
 * @param parameters the input from user
 * @param parameters_len
 * @param complex_array the set that exists in the program
 * @return OK if the input is ok, detailed information otherwise
 */
enum info set_bin_op_params(command cmd, char **parameters, int parameters_len) {
    enum info info;
    info = OK;
    if (parameters_len > 2){
        info= EXTRA_TEXT;
    }
    if (parameters_len < 2){
        info= MISSING_PARAM;
    }
    if (info==OK){
        cmd->complex_arg1_pos= pick_complex_var(parameters[0], &info);
        if(op_with_const(cmd->action)){
            info= set_const_arg(cmd, parameters[1]);
        } else{
            cmd->complex_arg2_pos= pick_complex_var(parameters[1], &info);
        }
    }
    return info;
}

/**
 * set the arguments of print_set command
 * @param cmd the command object that hold the information
 * @param parameters the input from user
 * @param parameters_len
 * @param complex_array the set that exists in the program
 * @return OK if the input is ok, detailed information otherwise
 */
enum info set_unary_param(command cmd, char **parameters, int parameters_len) {
    enum info info;
    info=OK;
    if (parameters_len > 1){
        return EXTRA_TEXT;
    }
    if (parameters_len==0){
        return MISSING_PARAM;
    }
    cmd->complex_arg1_pos= pick_complex_var(parameters[0], &info);
    return info;
}

/**
 * check the validity of the  commas in one line.
 * @param line the input from the user
 * @return OK if the input is ok, detailed information otherwise
 */
enum info check_commas(char line[]) {
    enum state {BEFORE_OP, AFTER_OP, GETTING_OP, BEFORE_ARG, GETTING_ARG, AFTER_ARG};
    enum state current=BEFORE_OP;
    enum info result=OK;
    char tmp_char;
    int i;
    unsigned long length;
    length= strlen(line);
    i=0;
    while (result==OK && i<length){
        tmp_char = line[i];
        switch (current){
            case BEFORE_OP:
                if (tmp_char==SEPARATOR){
                    result= ILLEGAL_COMMA;
                }
                if (!isspace(tmp_char)){
                    current = GETTING_OP;
                }
                break;
            case GETTING_OP:
                if (tmp_char==SEPARATOR){
                    result= ILLEGAL_COMMA;
                }
                if (isspace(tmp_char)){
                    current=BEFORE_ARG;
                }
                break;
            case BEFORE_ARG:
                if (tmp_char==SEPARATOR){
                    result= ILLEGAL_COMMA;
                }
                if (!isspace(tmp_char)){
                    current=GETTING_ARG;
                }
                break;
            case GETTING_ARG:
                if (isspace(tmp_char)){
                    current = AFTER_ARG;
                }
                if (tmp_char==SEPARATOR){
                    current = BEFORE_ARG;
                }
                break;
            case AFTER_ARG:
                if (tmp_char==SEPARATOR){
                    current = BEFORE_ARG;
                    break;
                }
                if (!isspace(tmp_char)){
                    result= MISSING_COMMA;
                }
            default:
                continue;
        }
        ++i;
    }
    if(line[length-1]==SEPARATOR){
        result=ILLEGAL_COMMA;
    }
    return result;
}