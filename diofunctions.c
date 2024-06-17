/** by HelderJFLima **/

/* Functions used in the 'diophantine' program */


#include <direct.h>          /* _getcwd */
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxfunctions.h"

#define A       0            /* For array indexing */
#define B       1
#define C       2
#define X       0
#define Y       1
#define BASE    10           /* Base used in strtol function (stdlib.h) */
#define EQSIZE  3            /* Equation size */
#define GETDIR  _getcwd      /* Function to get the directory name */
#define SOLSIZE 2            /* Solution size */


void discriminantForm(int *presol, const int *simplif)
{
	int temp;

	presol[X] *= simplif[C];

	presol[Y] *= simplif[C];

	if( presol[X] >= simplif[B] )
	{
		temp = presol[X] / simplif[B];

		presol[X] %= simplif[B];

		temp *= simplif[A];

		presol[Y] = temp - presol[Y];
	}
	else
		presol[Y] = -presol[Y];
}


void fillOutput(int *output, const int *equation,
                const int *sol, const int *simplif)
{
	int i;

	for(i = 0; i < EQSIZE; i++)
		*output++ = *equation++;

	if(*sol >= 0)                       /* If there is a solution */
	{
		for(i = 0; i < SOLSIZE; i++)
			*output++ = *sol++;

		for(i = 0; i < SOLSIZE; i++)
			*output++ = *simplif++;
	}
}


int gcd(int a, int b)
{
	int c;      /* Auxiliary variable */
	int d;      /* To get the gcd */
	int r;      /* Remainder */

	if(b > a)                   /* Only a >= b */
		swapIntegers(&a, &b);

	d = a;

	r = b;

	while(r)                    /* Euclid's Algorithm */
	{
		c = d;

		d = r;

		r = c % d;
	}

	return d;
}


char* getFileName(const char *fname, const int *equation, const char *extension)
{
	int size;                /* Size of an array */
	int check;               /* To check error */
	char *filename = NULL;   /* String for the file name */

                                           /* Enough space to accommodate all */
	size = strlen(fname) +                 /* strings and avoid overflow      */
		   3 * (int)ceil( log10(INT_MAX) ) + strlen(extension) + 10;

	filename = (char*)calloc( size, sizeof(char) );

	if(filename == NULL)
	{
		perror("\ngetfilename->calloc");

		return NULL;
	}
	
	if(equation[B] > 0)                                   /* Write the string */
	{
		check = sprintf(filename, "%s%dx+%dy=%d%s", fname,
                        equation[A], equation[B], equation[C], extension);
	}
	else
	{
		check = sprintf(filename, "%s%dx%dy=%d%s", fname,
                        equation[A], equation[B], equation[C], extension);
	}

	if(check < 0)                                        /* If sprintf failed */
	{
		perror("\ngetfilename->sprintf");

		free(filename);

		return NULL;
	}
	
	return filename;
}


int isInvalidInput(int num, const char* const* args, int *integers)
{
	const char* const* pargs = args;            /* Auxiliary pointers */
	int *pinteg = integers;
	long number;

	if(num != 4)
		return 1;

	while(*++pargs)                             /* Check all arguments */
	{
		if( isInvalidString(*pargs) )
			return 1;
	}

	pargs = args;

	while(*++pargs)                             /* Convert strings to numbers */
	{
		number = strtol(*pargs, NULL, BASE);

		if(number <= INT_MIN || number >= INT_MAX)         /* Out of range */

			return 1;

		else
			*pinteg++ = (int)number;
	}
                                                           /* Invalid signals */
	if( integers[A] <= 0 || integers[B] == 0 || integers[C] <= 0 )
		return 1;

	return 0;
}


void minimalSolution(int *sol, const int *simplif)
{
	int minfact;          /* Auxiliary parameter */

	sol[X] *= simplif[C];

	sol[Y] *= simplif[C];

	minfact = (int)fmin( (double)( sol[X] / simplif[B] ),
                         (double)( sol[Y] / simplif[A] ) );

	sol[X] -= minfact * simplif[B];

	sol[Y] -= minfact * simplif[A];
}


int preSolution(int *sol, const int *simplif)
{
	int aux[2];
	int i = 1;
	int swapped = 0;
	int *number = NULL;      /* Integer arrays */
	int *quotient = NULL;

	number = allocateArray( simplif[A], simplif[B] );

	if(number == NULL)
	{
		printf("\npreSolution->allocateArray: error allocating array\n");

		return 1;
	}

	quotient = allocateArray( simplif[A], simplif[B] );

	if(quotient == NULL)
	{
		free(number);

		printf("\npreSolution->allocateArray: error allocating array\n");

		return 1;
	}

	number[0] = simplif[A];

	number[1] = simplif[B];

	if( number[0] < number[1] )                /* Only number[0] >= number[1] */
	{
		swapIntegers( &number[0], &number[1] );

		swapped = 1;
	}

	while( number[i] )                         /* Euclid's Algorithm */
	{
		number[i + 1] = number[i - 1] % number[i];

		quotient[i] = number[i - 1] / number[i];

		i++;
	}

	i -= 2;                   /* Adjust the position */

	sol[X] = 1;

	sol[Y] = (i != 0) ? ( -quotient[i] ) : ( 1 - number[0] );

	free(number);

	while(i > 1)              /* Find (x,y) that satisfies ax + by = gcd(a,b) */
	{
		i--;

		aux[X] = 1;

		aux[Y] = -quotient[i];

		aux[X] *= sol[Y];

		aux[Y] *= sol[Y];

		aux[Y] += sol[X];

		sol[X] = aux[X];

		sol[Y] = aux[Y];
	}

	free(quotient);

	if(swapped)
		swapIntegers( &sol[X], &sol[Y] );

	if(sol[X] < 0)                           /* Only x > 0 */

		alternativeSolution(sol, simplif);

	else
		sol[Y] = -sol[Y];                    /* Solution with absolute values */

	return 0;
}


void printPath(const char *fname)
{
	char *dirname = NULL;             /* Directory name */

	dirname = GETDIR(NULL, _MAX_DIR); /* Get the name of the current directory */

	if(dirname == NULL)
	{
		printf("\nprintPath->GETDIR: error writing directory name\n");

		return;
	}

	printf("%s\\%s", dirname, fname);          /* Display the path */

	free(dirname);
}


void printResults(const int *output)
{
	printf("\n\nEquation:\n\n%dx ", output[0] );

	if(output[1] > 0)

		printf("+ %dy = %d\n", output[1], output[2] );

	else
		printf("- %dy = %d\n", -output[1], output[2] );

	if(output[6] != 0)                           /* If there is a solution */
	{
		printf("\n\nSolution:\n\nx = ");

		if(output[3] != 0 && output[6] != 1)

			printf("%d + %dt\n", output[3], output[6] );

		else if(output[3] != 0)

			printf("%d + t\n", output[3] );

		else if(output[6] != 1)

			printf("%dt\n", output[6] );

		else
			printf("t\n");

		if(output[1] > 0)                        /* ax + by = c => Y = y - at */
		{
			printf("\ny = ");

			if(output[5] != 1)

				printf("%d - %dt\n", output[4], output[5] );

			else
				printf("%d - t\n", output[4] );
		}
		else                                     /* ax - by = c => Y = y + at */
		{
			printf("\ny = ");

			if(output[4] != 0 && output[5] != 1)

				printf("%d + %dt\n", output[4], output[5] );

			else if(output[4] != 0)

				printf("%d + t\n", output[4] );

			else if(output[5] != 1)

				printf("%dt\n", output[5] );

			else
				printf("t\n");
		}

		printf("\nwhere t is a natural number.\n\n");
	}
	else
		printf("\n\nThe equation has no natural solutions.\n\n");
}


int saveResults(const int *output, const char *fname)
{
	FILE *file;

	file = fopen(fname, "w");                       /* Create the file */

	if(file == NULL)
	{
		perror("\nsaveResults->fopen");

		return 1;
	}
                                                    /* Write the file */
	fprintf(file, "Equation:\n\n%dx ", output[0] );

	if(output[1] > 0)

		fprintf(file, "+ %dy = %d\n", output[1], output[2] );

	else
		fprintf(file, "- %dy = %d\n", -output[1], output[2] );

	if(output[6] != 0)                              /* If there is a solution */
	{
		fprintf(file, "\n\nSolution:\n\nx = ");

		if(output[3] != 0 && output[6] != 1)

			fprintf(file, "%d + %dt\n", output[3], output[6] );

		else if(output[3] != 0)

			fprintf(file, "%d + t\n", output[3] );

		else if(output[6] != 1)

			fprintf(file, "%dt\n", output[6] );

		else
			fprintf(file, "t\n");

		if(output[1] > 0)                        /* ax + by = c => Y = y - at */
		{
			fprintf(file, "\ny = ");

			if(output[5] != 1)

				fprintf(file, "%d - %dt\n", output[4], output[5] );

			else
				fprintf(file, "%d - t\n", output[4] );
		}
		else                                     /* ax - by = c => Y = y + at */
		{
			fprintf(file, "\ny = ");

			if(output[4] != 0 && output[5] != 1)

				fprintf(file, "%d + %dt\n", output[4], output[5] );

			else if(output[4] != 0)

				fprintf(file, "%d + t\n", output[4] );

			else if(output[5] != 1)

				fprintf(file, "%dt\n", output[5] );

			else
				fprintf(file, "t\n");
		}

		fprintf(file, "\nwhere t is a natural number.\n\n");
	}
	else
		fprintf(file, "\n\nThe equation has no natural solutions.\n\n");

	if( ferror(file) )                         /* Check if there was an error */
	{
		printf("\nsaveResults->fprintf: error writing information to file\n");

		fclose(file);

		return 1;
	}

	fclose(file);                              /* Close the file */

	return 0;
}


void simplifyEquation(int *simplif, const int *equation, int gcd)
{
	int i;

	for(i = 0; i < EQSIZE; i++)
		simplif[i] = equation[i] / gcd;

	if(simplif[B] < 0)                     /* Only positive values */
		simplif[B] = -simplif[B];
}