// Game of Life
// Timothy G. Day

#ifndef TWOD_H_
#define TWOD_H_

// Function prototypes:
//twoD.c
int** make2Dint(int nrows, int ncolumns);
char** make2Dchar(int nrows, int ncolumns);
int areEqual(char **arrayA, int rowsA, int columnsA, char **arrayB, int rowsB, int columnsB);
void printArray(char** array, int height, int width);
char** changeChar(char** array,int height, int width);
char** makeBlankArray(int nrows, int ncolumns);
char** makeCenteredArray(char** array, int nrows, int ncolumns, int orows, int ocolumns);
char** playOneRound(char** array, int nrows, int ncolumns);
int currentNeighbors(char** array, int nrows, int ncolumns, int currentRow, int currentColumn);
int isOccupied(char** array, int nrows, int ncolumns, int currentRow, int currentColumn);
int isDead(char **array, int rows, int columns);
//import.c
char** makeArrayFromFile(FILE* file);
int fileWidth(FILE* file);
int fileHeight(FILE* file);




#endif /* 2D_H_ */
