// IO.h

//This file is meant to deal with all functions that are used for input and output.
//This will include print functions that we're going to use.

/*Current iteration:

The inputted Markov Chain matrix will be placed in Matrix.txt. 

Each value will be in the form "number, number, number]" where "]" signals the end of the element. 

*/


//inputMarkovChain aims to read a matrix from a file for A. It then reads
//The initial conditions for the initial conditions for the vector b

//If 1 is returned, this process is successful, if 0 is returned there is an error. 
int inputMarkovChain(listMatrix * curr, int dimSize);

int inputInitialConditions(double * conditions, int dimSize);


//printVector takes a vector b and prints every element in a row.
void printVector(Chain * chain, double * b);

void outputResults(Chain * chain);