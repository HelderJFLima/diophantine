/** by HelderJFLima **/

/*
*
* This program calculates the natural solutions of linear Diophantine equations.
* The program must be called together with 3 arguments that indicate the values ​
* present in the equation.
*
* For more information, look for the README file.
*
*/


#include <stdio.h>
#include <stdlib.h>
#include "diofunctions.h"

#define A         0                       /* For array indexing */
#define B         1
#define C         2
#define Y         1
#define EQSIZE    3                       /* Equation size */
#define EXTENSION ".txt"                  /* File name extension */
#define FILENAME  "DiophantineEquation_"
#define OPSIZE    7                       /* Output array size */
#define SOLSIZE   2                       /* Solution size */


/* Calculate the natural solutions of a linear Diophantine equation. */

int main( int argc, char *argv[] )
{
	int equation[EQSIZE] = { 0 };      /* Equation terms */
	int simplified[EQSIZE] = { 0 };    /* Simplified equation */
	int solution[SOLSIZE] = { 0 };     /* Solution of the equation */
	int output[OPSIZE] = { 0 };        /* Values for the output */
	int error = 0;                     /* For error checking */
	int gcdiv = 1;                     /* Greatest common divisor */
	char *filename = NULL;             /* Output file name */

	if( isInvalidInput(argc, argv, equation) )
	{
		printf("\n\nInvalid input.\n\n"
               "The input arguments must be 3 integers A, B, C.\n\n"
               "The numbers must be non-zero and A and C must be positive.\n\n");

		return 1;
	}

	if(equation[B] > 0)                               /* ax + by = c */
	{
		gcdiv = gcd( equation[A], abs( equation[B] ) );

		if(equation[C] % gcdiv == 0)
		{
			simplifyEquation(simplified, equation, gcdiv);

			error = preSolution(solution, simplified);

			if(error)
			{
				printf("\nmain->preSolution: "
                       "error when determining the pre-solution\n");

				return 2;
			}

			discriminantForm(solution, simplified);

			if(solution[Y] > 0)                       /* There is a solution */

				fillOutput(output, equation, solution, simplified);

			else
				solution[A] = -1;
		}
	}
	else                                              /* ax - by = c */
	{
		gcdiv = gcd( equation[A], abs( equation[B] ) );

		if(equation[C] % gcdiv == 0)                  /* There is a solution */
		{
			simplifyEquation(simplified, equation, gcdiv);

			error = preSolution(solution, simplified);

			if(error)
			{
				printf("\nmain->preSolution: "
                       "error when determining the pre-solution\n");

				return 3;
			}

			minimalSolution(solution, simplified);

			fillOutput(output, equation, solution, simplified);
		}
		else
			solution[A] = -1;                         /* There is no solution */
	}

	if(output[0] == 0)
		fillOutput(output, equation, solution, simplified);

	printResults(output);

	filename = getFileName(FILENAME, equation, EXTENSION);

	if(filename == NULL)
	{
		printf("\nmain->getFileName: error getting file name\n");

		return 4;
	}

	error = saveResults(output, filename);

	if(error)
	{
		printf("\nmain->saveResults: "
               "error when saving results to output file\n");
	}
	else
	{
		printf("\n\nThe results were saved in:\n\n");

		printPath(filename);

		printf("\n\n");
	}

	free(filename);

	return 0;
}