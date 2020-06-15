// Game of Life
// Timothy G. Day

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"

/** Make a 2D array of integers.
 * @param nrows Number of rows.
 * @param ncolumns Number of columns.
 * @return Pointer to the array of pointers to the rows; null if unable to allocate memory; will not free partially-allocated memory.
*/
int** make2Dint(int nrows, int ncolumns) {

	int **a;                              // Array of pointers to rows
	unsigned int i = 0;                       // Loop counter

	// First allocate the array of pointers to rows
	a = (int **) malloc(nrows * sizeof(int *));

	// Determine if you can allocate the array
	if (!a) {
		// Unable to allocate the array
		return (int **) NULL;
	}

	// Now allocate array for each row
	for (i = 0; i < nrows; i++) {
		// LOOP INVARIANT: the count is less than the number of rows

		// i is the row we are about to allocate
		a[i] = malloc(ncolumns * sizeof (int));

		// Determine if you can allocate
		if (!a[i]) {
			// Unable to allocate
			return (int **) NULL;
		}
	}
	return a;
}

/** Make a 2D array of characters.
 * @param nrows Number of rows.
 * @param ncolumns Number of columns.
 * @return Pointer to the array of pointers to the rows; null if unable to allocate memory; will not free partially-allocated memory.
*/
char** make2Dchar(int nrows, int ncolumns) {

	char **a;                              // Array of pointers to rows
	unsigned int i = 0;                        // Loop counter

	// First allocate the array of pointers to rows
    a = (char **) malloc(nrows * sizeof(char *));

    // Determine if you can allocate the array
    if (!a) {
		// Unable to allocate the array
		return (char **) NULL;
	}

	// Now allocate array for each row
	for (i = 0; i < nrows; i++) {
		// LOOP INVARIANT: the count is less than the number of rows

		// i is the row we are about to allocate
		a[i] = malloc(ncolumns * sizeof (char));

		// Determine if you can allocate
		if (!a[i]) {
			// Unable to allocate
			return (char **) NULL;
		}
	}
	return a;
}

/** Find if two char arrays are equal
 * @param arrayA first array to be checked
 * @param rowsA numbers of rows in arrayA
 * @param columnsA numbers of columns in arrayA
 * @param arrayB second array to be checked
 * @param rowsB numbers of rows in arrayB
 * @param columnsB numbers of columns in arrayB
 * @return 1 if the arrays are equal, 0 if the arrays are not equal
 */
int areEqual(char **arrayA, int rowsA, int columnsA, char **arrayB, int rowsB, int columnsB) {

	int i = 0;                                         // Loop counter
	int j = 0;                                         // Loop counter
	int rows = rowsA;                              // Sets the number of rows
	int columns = columnsA;                        // Sets the number of columns

    //Checks if the arrays are same dimensions
	if(!(rowsA == rowsB && columnsA == columnsB)) {
		// The arrays have different dimensions
		return 0;
	}

	// Check each row for equivalence
    for(i = 0; i < rows; i++) {
    	// LOOP INVARIANT: the count is less than the total rows

    	// Check each entry in the row for equivalence
    	for(j = 0; j < columns; j++) {
    		// LOOP INVARIANTS: the count is less than the total columns

    		// Check if the two entries are the same
    		if(!(arrayA[i][j] == arrayB[i][j])) {
    			// The entries are different
    			return 0;
    		}
    	}
    }

    // No entries are found to be different; the arrays have the same dimensions
	return 1;
}

/** Print the given char array
 * @param array The array to be printed
 * @param height The number of rows the array has
 * @param width The number of columns the array has
*/
void printArray(char** array, int height, int width) {

	int i = 0;                             // The current row in the array
	int j = 0;                             // The current column in the array

	// Print each row
	for(i = 0; i < height; i++)  {
		// LOOP INVARIANT: The current row is less than or equal to the maximum row

		// Print each character in the row
		for(j = 0; j < width; j++) {
			// LOOP INVARIANT: The current column is less than or equal to the maximum column
			printf("%c", array[i][j]);
		}

		printf("\n");
	}
}

/** Replace blank space with a character
 * @param array The array to be printed
 * @param height The number of rows the array has
 * @param width The number of columns the array has
*/
char** changeChar(char** array,int height, int width) {

	int i = 0;                             // The current row in the array
	int j = 0;                             // The current column in the array

	// Print each row
	for(i = 0; i < height; i++)  {
		// LOOP INVARIANT: The current row is less than or equal to the maximum row

		// Print each character in the row
		for(j = 0; j < width; j++) {
			// LOOP INVARIANT: The current column is less than or equal to the maximum column
			if(array[i][j] != 'x') {
				array[i][j] = *"~";
			}
		}
	}
	return array;
}

/** Make an array with only blank spaces
 * @param nrows Number of rows
 * @param ncolumns Number of columns
 * @return An array with the right size and only blank spaces
 */
char** makeBlankArray(int nrows, int ncolumns) {

	char** array;                       // the array being created
	int i = 0;                          // The current row in the array
	int j = 0;                          // The current column in the array

	// Create new array
	array = make2Dchar(nrows, ncolumns);

	// Print each row
	for(i = 0; i < nrows; i++)  {
		// LOOP INVARIANT: The current row is less than or equal to the maximum row

		// Print each character in the row
		for(j = 0; j < ncolumns; j++) {
			// LOOP INVARIANT: The current column is less than or equal to the maximum column
			array[i][j] = ' ';
		}
	}
	return array;
}

/** Take the text in one array and center is in a new blank array
 * @param array The array containing the text to be centered
 * @oaram nrows The number of rows in the new array
 * @param ncolumns The number of columns in the new array
 * @oaram orows The number of rows in the old array
 * @param ocolumns The number of columns in the old array
 * @return The newly centered array
*/
char** makeCenteredArray(char** array, int nrows, int ncolumns, int orows, int ocolumns) {

	char** newArray;                    // The newly crafted array
	int offsetRows = 0;                 // The row offset needed to center the array
	int offsetColumns = 0;              // The column offset needed to center the array
	int i = 0;                          // The current row in the array
	int j = 0;                          // The current column in the array

	// Make sure the new array is big enough
	if(orows > nrows || ocolumns > ncolumns) {
		// The array is too small
		printf("ARRAY TOO SMALL 'makeCenteredArray' ERROR");
		return NULL;
	}

	// Is the different between rows even or odd?
	if((nrows - orows) % 2 == 0) {
		// Even
		offsetRows = ((nrows - orows) / 2);
	}
	else {
		// Odd
		offsetRows = (((nrows - orows) - 1) / 2);
	}

	// Is the different between columns even or odd?
	if((ncolumns - ocolumns) % 2 == 0) {
		// Even
		offsetColumns = ((ncolumns - ocolumns) / 2);
	}
	else {
		// Odd
		offsetColumns = (((ncolumns - ocolumns) - 1) / 2);
	}

	// Make the new blank array
	newArray = makeBlankArray(nrows, ncolumns);

	// Set each row
	for(i = 0; i < orows; i++)  {
		// LOOP INVARIANT: The current row is less than or equal to the maximum row

		// Set each character in the row
		for(j = 0; j < ocolumns; j++) {
			// LOOP INVARIANT: The current column is less than or equal to the maximum column
			newArray[i + offsetRows][j + offsetColumns] = array[i][j];
		}
	}
	return newArray;
}

/** Play one round of the game of life
 * @param array The initial array in the game
 * @param nrows The number of rows in the array
 * @param ncolumns The number of columns in the array
 * @return The next iteration in the game of life
*/
char** playOneRound(char** array, int nrows, int ncolumns) {

	char** newArray;                    // the array being created
	int i = 0;                          // The current row in the array
	int j = 0;                          // The current column in the array

	// Create new array
	newArray = makeBlankArray(nrows, ncolumns);

	// Set each row
	for(i = 0; i < nrows; i++)  {
		// LOOP INVARIANT: The current row is less than or equal to the maximum row

		// Set each character in the row
		for(j = 0; j < ncolumns; j++) {
			// LOOP INVARIANT: The current column is less than or equal to the maximum column

			// Is it occupied?
			if(array[i][j] == 'x') {
				// It is occupied

				// Take action based on number of neighbors
				switch(currentNeighbors(array, nrows, ncolumns, i, j)) {
					case 0:
						// 0n (Lonely)(Dies)
					    newArray[i][j] = ' ';
					    break;
					case 1:
						// 1n (Lonely)(Dies)
					    newArray[i][j] = ' ';
					    break;
					case 4:
						// 4n (Crowded)(Dies)
					    newArray[i][j] = ' ';
					    break;
					case 5:
						// 4n (Crowded)(Dies)
					    newArray[i][j] = ' ';
					    break;
					case 6:
						// 4n (Crowded)(Dies)
					    newArray[i][j] = ' ';
					    break;
					case 7:
						// 4n (Crowded)(Dies)
					    newArray[i][j] = ' ';
					    break;
					case 8:
						// 4n (Crowded)(Dies)
					    newArray[i][j] = ' ';
					    break;
					default:
						// Survives
						newArray[i][j] = 'x';
						break;
				}
			}
			else {
				// It is not occupied

				// Take action based on number of neighbors
				if(currentNeighbors(array, nrows, ncolumns, i, j) == 3) {
					// 3n (Birth)(Populate cell)
					newArray[i][j] = 'x';
				}
				else {
					// No birth
					newArray[i][j] = ' ';
				}
			}
		}
	}
	return newArray;
}

/** Returns the number of occupied neighbors in the array
 * @param array The initial array in the game
 * @param nrows The number of rows in the array
 * @param ncolumns The number of columns in the array
 * @param currentRow The row of the entry under consideration
 * @param currentColumn The column of the entry under consideration
 * @return The number of neighbors this cell has
*/
int currentNeighbors(char** array, int nrows, int ncolumns, int currentRow, int currentColumn) {
	int count = 0;                  // Number of Neighbors found so far

	// Check if cell is occupied (above)
	if(isOccupied(array, nrows, ncolumns, currentRow + 1, currentColumn)) {
		// Cell is occupied
		count++;
	}

	// Check if cell is occupied (top right)
	if(isOccupied(array, nrows, ncolumns, currentRow + 1, currentColumn + 1)) {
		// Cell is occupied
		count++;
	}

	// Check if cell is occupied (right)
	if(isOccupied(array, nrows, ncolumns, currentRow, currentColumn + 1)) {
		// Cell is occupied
		count++;
	}

	// Check if cell is occupied (bottom right)
	if(isOccupied(array, nrows, ncolumns, currentRow - 1, currentColumn + 1)) {
		// Cell is occupied
		count++;
	}

	// Check if cell is occupied (bottom)
	if(isOccupied(array, nrows, ncolumns, currentRow - 1, currentColumn)) {
		// Cell is occupied
		count++;
	}

	// Check if cell is occupied (bottom left)
	if(isOccupied(array, nrows, ncolumns, currentRow - 1, currentColumn - 1)) {
		// Cell is occupied
		count++;
	}

	// Check if cell is occupied (left)
	if(isOccupied(array, nrows, ncolumns, currentRow, currentColumn - 1)) {
		// Cell is occupied
		count++;
	}

	// Check if cell is occupied (top left)
	if(isOccupied(array, nrows, ncolumns, currentRow + 1, currentColumn - 1)) {
		// Cell is occupied
		count++;
	}
	return count;
}

/** Returns if cell is occupied
 * @param array The initial array in the game
 * @param nrows The number of rows in the array
 * @param ncolumns The number of columns in the array
 * @param currentRow The row of the entry under consideration
 * @param currentColumn The column of the entry under consideration
 * @return The 1 if cell is occupied, 0 if not or off array
*/
int isOccupied(char** array, int nrows, int ncolumns, int currentRow, int currentColumn) {

	// Check if reference is within array
	if(currentRow > (nrows - 1) || currentColumn > (ncolumns - 1) || currentRow < 0 || currentColumn < 0) {
		// Reference is outside of the array
		return 0;
	}

	// Check if cell has an x within it
	if(array[currentRow][currentColumn] == 'x') {
		// Contains an x
		return 1;
	}
	else {
		// Does not contain x
		return 0;
	}
	return 0;
}

/** Find if everything is dead
 * @param array first array to be checked
 * @param rows numbers of rows in arrayA
 * @param columns numbers of columns in arrayA
 * @return 1 if the array is dead, 0 if the arrays is not dead
 */
int isDead(char **array, int rows, int columns) {

	int i = 0;                                     // Loop counter
	int j = 0;                                     // Loop counter

	// Check is each row is dead
    for(i = 0; i < rows; i++) {
    	// LOOP INVARIANT: the count is less than the total rows

    	// Check each entry in the row is dead
    	for(j = 0; j < columns; j++) {
    		// LOOP INVARIANTS: the count is less than the total columns

    		// Check if the entry is dead
    		if(array[i][j] == 'x') {
    			// alive
    			return 0;
    		}
    	}
    }
    return 1;
}
