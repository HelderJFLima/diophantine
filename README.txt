This program calculates the natural solutions of linear Diophantine equations. It is based on the theory presented in section 6.1 of the book 'Elementos de Aritmética', by A. Hefez, published by the Brazilian Mathematical Society (2006, 2nd edition). As far as I know, this book only exists in Portuguese, but it is certainly possible to find something on this subject in other books that deal with Diophantine equations.

A linear Diophantine equation has the form ax + by = c, where a, b and c are non-zero integers. The values ​​a and c are positive, and the value b can be positive or negative. The program must be called together with 3 arguments that indicate the values ​​present in the equation.

Assuming, for example, the equations 3x + 4y = 5 and 3x - 4y = 5, it is necessary to use the commands:

diophantine 3 4 5

and

diophantine 3 -4 5

If the user provides arguments that do not comply with this model, he will receive an error message and nothing will be done. If the arguments are correct, the program will calculate the solutions to the equation, if any, and will display the result to the user. It will also generate a file with the result in the folder from which it is being called. The name of the file will indicate the equation that the user entered. If there are no natural solutions, there will be a message indicating this.

The comments in the program code do not attempt to explain in detail what is happening from a mathematical point of view. That would be impractical. To understand the logic of the algorithms, it is necessary to study the mathematical theory involved in detail. Therefore, I am only providing in this file the indication of the necessary source for those who wish to delve deeper into the subject. I can only guarantee that the program passed the tests I performed. :)


by HelderJFLima