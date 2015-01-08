#define ELEMENTSPACE 120

//Markov.h


//The markovType Structs contain the separate vectors that are available depending
//On time.

//A matrix ADT defines the matrix

typedef struct matrix Matrix;

struct matrix{
   double * row; //Contains the elements in the row
   int rowNumber; //Lists the row number of the current row
   Matrix * next; //Lists where the next row is
   Matrix * firstRow; //Lists which row is the first row of the Matrix.
};

//A selection ADT uses a matrix except it contains a selection of terms involved
typedef struct listMatrixStruct listMatrix;

struct listMatrixStruct{
    double * element; //Contains the list of elements
    int rowNumber;
    int columnNumber;
    int elementSize; // Contains the size of the Element involved
    listMatrix * next;
    listMatrix * firstElement;
};

typedef struct NodeStruct Node;

struct NodeStruct{
   double * stateVector;
   Node * next;
   Node * prev;
};

//The chain Type provides information on the location of different MarkovType 
//Structs 
typedef struct ChainStruct{
   Node * first;
   Node * last;
   int numberOfNodes;
   int dimSize;
}Chain;

/*
 * Functions which affect the Matrix ADT
 * 
 */

//Creates matrix ADT
Matrix * newMatrix(int dimSize);

//Frees matrix ADT
void freeMatrix(Matrix * delMatrix);

//Adds new Row to Matrix ADT
Matrix * addNewRow(Matrix * matrix, int dimSize);

//Prints Matrix
void printMatrix(Matrix * matrix, int dimSize);

/*
 * Functions that affect the listMatrix ADT
 * 
 */

//Creates listMatrix ADT
listMatrix * newListMatrix(void);

//Frees listMatrix ADT
void freeListMatrix(listMatrix * delListMatrix);

//Adds a new element to the list matrix
void insertIntoElement(listMatrix * curr, double number);

//If a new element needs to be created, then we create the next element that is involed.
listMatrix * createNextElement(listMatrix * curr, int dimSize);

//Picks a random element and places it in the picked matrix for all elements
Matrix * pickRandomItem(listMatrix * curr, int dimSize);


/*
 * Functions which affect Chain ADT
 * 
 */


//Creates Chain ADT
Chain * newChain(int dimSize);

//Frees Chain ADT
void freeChain(Chain * delChain);

//Creates the Markov ADT
//Node * createNode(Chain * chain);

//Deletes the created node
//When we're freeing the nodes, we're removing the all of the nodes from the first term
//To the last.
//If we successfully freed the node, return 1 else return 0
int freeNode(Chain * chain);

//Adds new node to MarkovChain.
Node * addNewNode(Chain * chain, double * initState);

void printNode(Chain * chain, Node * node);
