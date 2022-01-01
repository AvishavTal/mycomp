#ifndef COMMAND
#define COMMAND
#include "mycomp.h"
#include "complex.h"

/**
 * hold the information of a command
 */
typedef struct cmd *command;

/*assign the fildes of the given command according to the input from the user.
 * cm - the pointer of the command to be assigned.*/
enum info set_command(command cm, char *line);

/*run the given command.*/
void run_command(command cm, complex complex_array[]);

/**
 * @return  a new command
 */
command init_command();

/**
 * @param command1
 * @return the result of the given command
 */
complex get_result(command command1);

/**
 * @param cm
 * @return the action name of the command.
 */
char *get_action(command cm);

#endif