#include "markov.h"
#include "IO.h"
#include "calc.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//This is the standard function we're going to be using once we've finished 
//writing up test cases

int main(argc, argv){
   //First ask for the number of elements in the Markov Chain and the precision required
   int dimSize = inputDimSize();
   //double precision = inputPrecision();
   
   //Then create the listMatrix called FuzzyMatrix
   listMatrix * fuzzyMatrix = newListMatrix();
   
   //Then we create a new Chain which contains our information for the vectors
   Chain * stateInfo = newChain(dimSize);
   
   /**
    * The following code is for dealing with inputs into the system
    * 
    */
   
   //Then read IO for the listMatrix for the file
   int inputSuccess = inputMarkovChain(fuzzyMatrix, dimSize);
   
   double initConds[dimSize];
   
   //That is if the input function failed
   if(inputSuccess == 0){
      exit(0);
   }
   
   //now get data for the initial Conditions
   inputSuccess = inputInitialConditions(initConds, dimSize);
   
   //After that we add the inital conditions to the Chain
   
   Node * currVector = addNewNode(stateInfo, initConds);
   
   //That is if the input function failed
   if(inputSuccess == 0){
      exit(0);
   }
  
  //First create the new Matrix
   Matrix * iteration;
   
   /*
    * 
    * Next we try to create a forward list of nodes
    * 
    */
   int isPrecise = 0;
   //Keep on iterating until we have a suitably precise answer   
   while(isPrecise < 1000){
   
       //First create the new Matrix
       iteration = newMatrix(dimSize);
   
       //Then pick random numbers to fill the Matrix
       Matrix * iteration = pickRandomItem(fuzzyMatrix, dimSize);
       printf("Iteration %d : \n", isPrecise);
       printMatrix(iteration, dimSize);
       markovMultiply(iteration, stateInfo);
//       isPrecise = compareVectors(stateInfo, precision);
       freeMatrix(iteration);
       isPrecise++;
   }
   
   /*
    * 
    * Finally, we do outputs...
    * 
    */
   
   outputResults(stateInfo);
   
   return 0;
}

int inputDimSize(void){
   int dimSize;

   printf("How many vectors in your model? \n");
   scanf("%d \n", &dimSize);
   

   //That is, if the dimension size is negative
   if (dimSize <= 0){
      printf("This isn't a valid size \n");
      //If this doesn't work, apply this function recursively
      dimSize = inputDimSize();
   }
   printf("Dimsize required is %d \n", dimSize);
   return dimSize;
}

double inputPrecision(void){
   double precision;
   
   printf("Whats the precision that you require? \n");
   scanf("%lf \n", &precision);

   if (precision < 0 || precision > 1){
      printf("Precision value incorrect. Please try again \n");
      precision = inputPrecision();
   }
   return precision;
}
