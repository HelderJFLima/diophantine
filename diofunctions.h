/** by HelderJFLima **/

/* Header of functions used in the 'diophantine' program */


#ifndef DIOFUNCTIONS_H
#define DIOFUNCTIONS_H


/* Change the form of a pre-solution to allow checking whether there is a
** solution or not.
*/
void discriminantForm(int *presol, const int *simplif);


/* Fill an array with the information for the output.
*/
void fillOutput(int *output, const int *equation,
                const int *sol, const int *simplif);


/* Calculate the greatest common divisor of two non-zero natural numbers.
*/
int gcd(int a, int b);


/* Assembles the name of a string from the information provided; return a
** pointer to the created string or NULL if something goes wrong.
*/
char* getFileName(const char *fname, const int *equation, const char *extension);


/* Check if arguments are invalid; return 1 if yes and 0 if not.
*/
int isInvalidInput(int num, const char* const* args, int *integers);


/* Determine a minimal solution from a pre-solution.
*/
void minimalSolution(int *sol, const int *simplif);


/* Determine a pre-solution (x,y) that satisfies ax + by = gcd(a,b); return 1 if
** an error occurs during execution and 0 otherwise.
*/
int preSolution(int *sol, const int *simplif);


/* Display the directory path where the output file was saved.
*/
void printPath(const char *fname);


/* Display the results on the screen.
*/
void printResults(const int *output);


/* Save the results to a file; return 1 if there is an error in the recording
** and 0 otherwise.
*/
int saveResults(const int *output, const char *fname);


/* Simplify the terms of an equation by dividing them by the greatest common
** divisor of the first two.
*/
void simplifyEquation(int *simplif, const int *equation, int gcd);


#endif	/* DIOFUNCTIONS_H */