
#include "complex.h"

/**
 * hold the information of a command
 */
typedef struct cmd *command;

/**
 * information about validity of the input
 */
enum info {OK,EOF_E, UNDEFINED_VAR, UNDEFINED_COMMAND,NOT_DOUBLE,
    LIST_TERMINATION, MISSING_PARAM, EXTRA_TEXT, ILLEGAL_COMMA, MISSING_COMMA,BLANk_LINE};



/*assign the fildes of the given command according to the input from the user.
 * cm - the pointer of the command to be assigned.*/
int get_command(command cm);

/*run the given command.*/
void run_command(command cm, complex complex_array[]);

/**
 * print the result of the given command.
 * @param cm
 */
void print_result(command cm);
/**
 * @return  a new command
 */
command init_command();
