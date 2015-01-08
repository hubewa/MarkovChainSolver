//Calc.h

void markovMultiply(Matrix * A, Chain * chain);

int compareVectors(Chain * chain, int precision);

double * matrixMultiply(Matrix * A, double * b, int dimSize);

//This function applies the activation Function to the result
double activationFunction ( double result);

//Normalises the vector. Returns the normalisation constant
double normalisation(double * a, int dimSize);