#include "markov.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void markovMultiply(Matrix * A, Chain * chain){
   double * prevVector = chain->last->stateVector;
   double * newVector = matrixMultiply(A, prevVector, chain->dimSize);
   printVector(chain, newVector);
   addNewNode(chain, newVector);
   
}

int compareVectors(Chain * chain, int precision){
   Node * firstNode = chain->last;
   Node * secondNode = firstNode->prev;
   
   int i;
   int compare = 1;
   for(i = 0; i < chain->dimSize; i++){
      double compareNumber = (firstNode->stateVector[i] - secondNode->stateVector[i])/firstNode->stateVector[i];
      if (abs(compareNumber) > precision){
         compare = 0;
      }
   }

   return compare;
}




double * matrixMultiply(Matrix * A, double * b, int dimSize){
  
   double * newVector = malloc(dimSize * sizeof(double));
   int i;
   int j;
   double sum;

   if(A->rowNumber != 1){
      A = A->firstRow;
   }
   
   
   for (i = 0; i < dimSize; i++){
      sum = 0;      
      for(j = 0; j < dimSize; j++){
         sum = sum + (A->row[j]) * b[j];
      }
      
      //Now apply the activation function
      sum = activationFunction(sum);
      
      newVector[i] = sum;
      
      A = A->next;
   }
   return newVector;
}

double activationFunction(double result){
  double answer;
  answer = (-4) * (result - 0.5);
  answer = exp(answer); //taking the exponential of the result above
  answer = 1 + answer;
  answer = 1/answer;
  return answer;
}

double normalisation(double * a, int dimSize){
  //First sum up all of the terms
  double sum = 0;
  int i;
  for(i = 0; i < dimSize; i++){
    sum = sum + pow(a[i],2);
  }
  printf("sum = %lf \n", sum);
  
  //Then take the square root
  double constant = sqrt(sum);
  return constant;
  
}
