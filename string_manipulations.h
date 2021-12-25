
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/**
 * trim the whitespaces fron the edges of the given string
 * @param str
 * @return
 */
char *trim_whitespace(char *str);
/**
 * split the given string to several strings
 * @param src the string to split
 * @param dest 2D array to hold the otput strings
 * @param delimiter
 * @return the number of strings
 */
int split(char *src, char **dest, const char *delimiter);

/**
 * convert string to a floating point number
 * @param str string to convert
 * @return 0 iff the string contains non numeric chars
 */
int str_to_double(char *str, double *dest);

/**
 * check if given string represent the number zero.
 * @param str
 * @return 0 iff str is not representation of 0.
 */
char is_zero(char *str);