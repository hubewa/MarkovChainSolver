//Input output

#include "markov.h"
#include "IO.h"
#include <stdio.h>
#include <stdlib.h>


//I assume that a fresh listMatrix was created
int inputMarkovChain(listMatrix * curr, int dimSize){
   //Open the file first
  FILE *fp = fopen("matrix.txt", "r"); //This is the file we read from
  
  //Now setting some arrays so that we can read from the data
  double entry;
  char buff[100];
  
  if(fp == NULL){
    printf("Matrix File cannot be opened \n");
    return 0;
  } else {
     printf("Matrix File has been successfully opened \n");
     while(!feof(fp)){
         fscanf(fp, "%lf", &entry);
	insertIntoElement(curr, entry);
	fscanf(fp, "%s", buff);
	//That is, if we reached the end of the element chain
	if(buff[0] == ']'){
	  curr = createNextElement(curr, dimSize);
	}
	
	
     }
     
     //The next line is only a temporary solution for now
     curr->elementSize = curr->elementSize - 1;
     
     if(curr->columnNumber != dimSize){
	printf("You've inputed the wrong dimSize or the wrong number of entries");  
	return 0;
     } else if (curr->rowNumber != dimSize){
	printf("You've inputted the wrong number of rows");
	return 0;
     }
     
     return 1;
  }
}

int inputInitialConditions(double * conditions, int dimSize){
   //Open the file first
   FILE *fp = fopen("initConds.txt", "r"); //This is the file that we read initial conditions from
   
   //Now setting some arrays so we can read from the data
   int entry;
   char buff[100];
  
   int i = 0;
   
   if(fp ==NULL){
      printf("Initial Conditions file cannot be opened \n");
   } else {
      printf("Initial Conditions file has been opened \n");
      while(!feof(fp) && i < dimSize){
	fscanf(fp, "%d %s", &entry, buff);
	conditions[i] = entry;
	i++;
      }
     
      
      //Error checking for data
      if(i < dimSize){
	printf("You have entered too few initial conditions \n");
	return 0;
      } else if (i > dimSize){
	printf("You've inputed too many initial conditions \n");
	return 0;
      }
   }
  return 1;
}


void printVector(Chain * chain, double * b){
   int i;
   for(i = 0; i < chain->dimSize; i++){
      printf("%f  ", b[i]);
   }
   printf("\n");
}

void outputResults(Chain * chain){
  //First set the file that you want to write to
    FILE *fp = fopen("Solutions.txt", "w");
  
    Node * curr = chain->first;
    
    int i = 0;
    //Do this until we reach the last vector
    while(curr != chain->last){
        //Do this until all of the results have been recorded
	while(i < chain->dimSize){
	  fprintf(fp, "%f ,", curr->stateVector[i]);
	  i++;
	}
	i = 0;
	fprintf(fp, "\n");
	curr = curr->next;
    }
    
    //This is for the last case
    while(i < chain->dimSize){
      fprintf(fp, "%f ,", curr->stateVector[i]);
      i++;
    }
}
