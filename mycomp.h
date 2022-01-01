#ifndef MYCOMP
#define MYCOMP
/*
 * indexes of the sets in the array
 */
#define A_IDX 0
#define B_IDX  1
#define C_IDX  2
#define D_IDX 3
#define E_IDX 4
#define F_IDX 5

/**
 * information about validity of the input
 */
enum info {OK,EOF_E, UNDEFINED_VAR, UNDEFINED_COMMAND,NOT_DOUBLE, MISSING_PARAM, EXTRA_TEXT, ILLEGAL_COMMA, MISSING_COMMA,BLANk_LINE};
#endif