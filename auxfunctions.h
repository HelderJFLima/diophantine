/** by HelderJFLima **/

/* Header of auxiliary functions used in the 'diophantine' program */


#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H


/* Allocate space for an array of numbers large enough to contain all the
** numbers used in Euclid's algorithm with 'a' and 'b'; return a pointer to the
** array or NULL if there is an error.
*/
int* allocateArray(int a, int b);


/* Change a pre-solution of type 'bY - aX = c' into one of type 'ax - by = c'.
*/
void alternativeSolution(int *sol, const int *simplif);


/* Test whether a string contains a decimal number in the correct format to be
** accepted as an argument; return 1 if the format is invalid and 0 otherwise.
*/
int isInvalidString(const char *str);


/* Swap the position of two integers.
*/
void swapIntegers(int *a, int *b);


#endif	/* AUXFUNCTIONS_H */