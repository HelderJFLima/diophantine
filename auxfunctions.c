/** by HelderJFLima **/

/* Auxiliary functions used in the 'diophantine' program */


#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define A 0             /* For array indexing */
#define B 1
#define X 0
#define Y 1


int* allocateArray(int a, int b)
{
	int size = 3;
	int *array = NULL;

	size += (a > b) ? (a % b) : (b % a);    /* Size is based on the remainder of */
                                            /* the division                      */

	array = (int*)calloc( size, sizeof(int) );

	if(array == NULL)
		perror("\nallocateArray->calloc");

	return array;
}


void alternativeSolution(int *sol, const int *simplif)
{
	int factor;

	sol[X] = -sol[X];

	factor = (int)fmax( (double)( sol[X] / simplif[B] ),
                        (double)( sol[Y] / simplif[A] ) );

	factor++;

	sol[X] = factor * simplif[B] - sol[X];

	sol[Y] = factor * simplif[A] - sol[Y];
}


int isInvalidString(const char *str)
{
	if(*str == '-' || *str == '+')       /* Possible sign */
	{
		str++;

		if(*str == '\0')
			return 1;
	}

	while(*str != '\0')
	{
		if( !isdigit(*str++) )
			return 1;
	}

	return 0;
}


void swapIntegers(int *a, int *b)
{
	int temp;

	temp = *a;

	*a = *b;

	*b = temp;
}