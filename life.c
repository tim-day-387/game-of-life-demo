// Game of Life
// Timothy G. Day

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"

/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
*/
int main(int argc, char **argv) {
	printf("Game of Life\n\n");

	// Input Arguements
	char *inputFileName = 0;                         // Name of file containing initial grid
	int nrows = 0;                                   // Number of rows in the grid
	int ncolumns = 0;                                // Number of columns in the grid
	int gens = 0;                                    // Number of generations to produce
	char doPrint = 'n';                              // y if user wants to print after each generation, n if not
	char doPause = 'n';                              // y if user wants to pause after each generation, n if not
	// Variables
	int w;                                           // number of columns in the file
	int h;                                           // number of rows in the file
	int g;                                           // generation tracker
	int endCause;                                    // 0 all dead; 1 repeat; 2 natural
	// Arrays
	char** fileData;                                 // Data from the file
	char** stateA;                                   // Centered data from file; most recent iteration of game of life
	char** stateB;                                   // Second most recent iteration of game of life
	char** stateC;                                   // Third most recent iteration of game of life

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return 1;
	}

	//Save the command-line arguments.
	nrows = atoi(argv[1]);                           // Convert from string to integer, save into variable
	ncolumns = atoi(argv[2]);                        // Convert from string to integer, save into variable
	gens = atoi(argv[3]);                            // Convert from string to integer, save into variable
	inputFileName = argv[4];                         // Convert from string to integer, save into variable

	// Find the correct number of arguements and save them
	switch (argc) {
		case 6:
			// Print was entered
			doPrint = *argv[5];
			break;
		case 7:
			// Print and pause were entered
			doPrint = *argv[5];
			doPause = *argv[6];
			break;
		default:
			break;
	}

	// Extract Data
	FILE* file = fopen(inputFileName, "r");          // Pointer to the beginner of the file
	w = fileWidth(file);                             // Record the file width
	rewind(file);                                    // Rewind file
	h = fileHeight(file);                            // Record the file height
	rewind(file);                                    // Rewind file
	fileData = makeArrayFromFile(file);              // Extract the file data into an array
	fclose(file);                                    // Close file

	// Initialize the game of life (gen 0)
	stateA = makeCenteredArray(fileData, nrows, ncolumns, h, w);  // Put the file data into stateA
	stateB = make2Dchar(nrows, ncolumns);                         // Intialize stateB with a char array
	stateC = make2Dchar(nrows, ncolumns);                         // Intialize stateC with a char array

	// Generate the require number of generations
	for(g = 1; g <= gens; g++) {
		// LOOP INVARIANT: The current generation is less than the maximum generation

		// Print this if print is enabled
		if(doPrint == 'y') {
			// Print
			printf("Generation: %d\n", g - 1);
			printArray(changeChar(stateA, nrows, ncolumns), nrows, ncolumns);
			fflush(stdout);
		}

		// Pause for ENTER if pause is enabled
		if(doPause == 'y') {
			// Pause
			while( getchar() != '\n');
		}

		// Advance each state by one level
		stateC = stateB;                                          // Save old state
		stateB = stateA;                                          // Save old state
		stateA = playOneRound(stateB, nrows, ncolumns);           // Generate new state by playing one round of the game

		// Find out end condition

		// Find if stateA equal to previous states
		if (areEqual(stateA, nrows, ncolumns, stateB, nrows, ncolumns) || areEqual(stateA, nrows, ncolumns, stateC, nrows, ncolumns)) {
			// StateA is equal to a previous state
			endCause = 1;
			break;
		}

		// Find if all are dead
		if(isDead(stateA, nrows, ncolumns)) {
			// All are dead
			endCause = 0;
			break;
		}
		endCause = 2;
	}

	// Print the final generation
	printf("Generation: %d\n", g);
	printArray(changeChar(stateA, nrows, ncolumns), nrows, ncolumns);

	// Print cause of end
	switch(endCause) {
		case 0:
			// All Dead
			printf("CAUSE: All organisms dead.\n");
			break;
		case 1:
			// Repetition
			printf("CAUSE: The pattern repeated.\n");
			break;
		case 2:
			// Natural
			printf("CAUSE: Finished the given number of generations.\n");
			break;
	}

	// Print number of generations
	printf("Completed in %d generations.\nInitial state is generation 0.\n", g);

	return 0;
}
