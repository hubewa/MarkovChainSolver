#include "markov.h"
#include <stdio.h>
#include <stdlib.h>

Matrix * newMatrix(int dimSize){
   Matrix * initMatrix = malloc(sizeof(Matrix));
   initMatrix->row = malloc(sizeof(double)*dimSize);
   initMatrix->rowNumber = 1;
   initMatrix->next = NULL;
   initMatrix->firstRow = initMatrix;
   return initMatrix;
}

void freeMatrix(Matrix * delMatrix){
   if(delMatrix->rowNumber != 1){
      delMatrix = delMatrix->firstRow;
   }
   
   int deleteCounter = 1;
   Matrix * nextRow;
   while(deleteCounter == 1){
      if(delMatrix->next == NULL){
         deleteCounter = 0;
      }
      nextRow = delMatrix->next;
      free(delMatrix->row);
      free(delMatrix);
      if(deleteCounter == 1) delMatrix = nextRow;
   }
}

Matrix * addNewRow(Matrix * matrix, int dimSize){
   Matrix * newRow = malloc(sizeof(Matrix));
   newRow->row = malloc(sizeof(double)*dimSize);
   newRow->rowNumber = matrix->rowNumber + 1;
   newRow->next = NULL;
   newRow->firstRow = matrix->firstRow;

   matrix->next = newRow;

   return newRow;
}

void printMatrix(Matrix * matrix, int dimSize){
   //Sets the Matrix to go to the first row;
   if(matrix->rowNumber != 1){
      matrix = matrix->firstRow;
   }
   
   int row;
   int column;
   for(row = 0; row < dimSize; row++){
      for(column = 0; column < dimSize; column++){
	printf("%lf   ", matrix->row[column]);
      }
      printf("\n");
      matrix = matrix->next;
   }
}

/*
 * 
 * Modifies listMatrix ADT
 * 
 */

listMatrix * newListMatrix (void){
  listMatrix * initListMatrix = malloc(sizeof(listMatrix));
  initListMatrix->element = malloc(sizeof(double) * ELEMENTSPACE);
  initListMatrix->rowNumber = 1;
  initListMatrix->columnNumber = 1;
  initListMatrix->elementSize = 0;
  initListMatrix->next = NULL;
  initListMatrix->firstElement = initListMatrix;

  return initListMatrix;
}

void freeListMatrix(listMatrix * delListMatrix){
  if(delListMatrix->rowNumber != 1){  
     delListMatrix = delListMatrix->firstElement;
    
  } else if (delListMatrix->columnNumber != 1){
     delListMatrix = delListMatrix->firstElement;
  }
  
  int nullFlag = 1;
  while(nullFlag == 1){
    listMatrix * tempListMatrix = delListMatrix; 
    if (delListMatrix->next == NULL){
      nullFlag = 0;
    } else {
       tempListMatrix = delListMatrix ->next;
    }
    free(delListMatrix->element);
    free(delListMatrix);
    delListMatrix = tempListMatrix;
  }
}

void insertIntoElement(listMatrix * curr, double number){
  if(curr->elementSize == 0){
     curr->element[0] = number;
  } else {
     curr->element[curr->elementSize] = number;
  } 
  curr->elementSize++;
}

listMatrix * createNextElement(listMatrix * curr, int dimSize){
   listMatrix * newElement = malloc(sizeof(listMatrix));
   curr->next = newElement;
   
   if(curr->columnNumber == dimSize){//This means that we have reached the end of the column
     newElement->rowNumber = curr->rowNumber + 1;
     newElement->columnNumber = 1;
   } else {
     newElement->rowNumber = curr->rowNumber;
     newElement->columnNumber = curr->columnNumber + 1;
   }
   
   
   newElement->element = malloc(sizeof(double) * ELEMENTSPACE);
   newElement->elementSize = 0;
   newElement->next = NULL;
   newElement->firstElement = curr->firstElement;
   return newElement;
}
     
Matrix * pickRandomItem(listMatrix * curr, int dimSize){
  int row;
  int column; //That is, row and column is to be initialised to be the first square and first row
  Matrix * random = newMatrix(dimSize);
  for(row = 0; row < dimSize; row++){
    for(column = 0; column < dimSize; column++){
      int seed = curr->elementSize;
      int randomNumber = rand() % seed;
      random->row[column] = curr->element[randomNumber];
      curr = curr->next;
    }
    if(row != dimSize) random = addNewRow(random, dimSize);  
  }
  return random;  
}


/*
 * Modifies Chain ADTs
 * 
 */

Chain * newChain(int dimSize){
   //Initialise elements inside the chain ADT
   //In this case, we assume that the chain i
   Chain * initChain = malloc(sizeof(Chain));
   initChain->first = NULL;
   initChain->last = NULL;
   initChain->numberOfNodes = 0;
   initChain->dimSize = dimSize;

   return initChain;
}

void freeChain(Chain * delChain){
   int freeNodeSuccess = 1;
   while (freeNodeSuccess == 1){
      freeNodeSuccess = freeNode(delChain);
   }   
   free(delChain);
}

/*
 * Modifies Node ADT
 * 
 */


int freeNode(Chain * chain){
   //First, find out whether we do have any nodes in the chain   
   if (chain->numberOfNodes == 0){
      return 0;
   }
   //Now we try to free the nodes   
   Node * delNode = chain->first;
   chain->first = delNode->next;
   free(delNode);

   if(chain->numberOfNodes == 1){
      chain->numberOfNodes = 0;
      chain->last = NULL;
   } else {
      (chain->numberOfNodes)--;
   }
   return 1;  
}

Node * addNewNode(Chain * chain, double * initState){
      //First consider boundary case, that is if first term is empty.
   Node * newNode = malloc(sizeof(Node));
   //Check if there are any elements in the chain first. Then we adjust chain
   if(chain->first == NULL){
      chain->first = newNode;
      chain->last = newNode;
      newNode->prev = NULL;      
   } else {
      Node * lastNode = chain->last;
      lastNode -> next = newNode;
      chain->last = newNode;
      newNode->prev = lastNode;
   }
   newNode->stateVector = initState;
   newNode->next = NULL;

   chain->numberOfNodes = chain->numberOfNodes + 1;
   
   return newNode;
}

void printNode(Chain * chain, Node * node){
    int i;
    for(i = 0; i < chain->dimSize; i++){
        printf("[   %lf   ] \n", node->stateVector[i]);
    }
    
}