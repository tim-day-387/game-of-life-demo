// Game of Life
// Timothy G. Day

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"

/** Turn FILE in character array.
 * @param file The file to be turned into an array.
 * @return An array of x's and blanks representing the file inputed.
*/
char** makeArrayFromFile(FILE* file) {

	int width = 0;                    // width of the text in the file
	int height = 0;                   // height of the text in the file
	char** array;                     // output array
	char i = ' ';                     // current char in text file
	char j = ' ';                     // previous char
	int a = 0;                        // current row in array
	int b = 0;                        // current column in array
	int h = 0;                        // current row in array
	int w = 0;                        // current column in array

	width = fileWidth(file);
	rewind(file);
	height = fileHeight(file);
	rewind(file);

	array = make2Dchar(height, width);

	// Blank each row
	for(h = 0; h < height; h++)  {
		// LOOP INVARIANT: The current row is less than or equal to the maximum row

		// Blank each character in the row
		for(w = 0; w < width; w++) {
			// LOOP INVARIANT: The current column is less than or equal to the maximum column
			array[h][w] = ' ';
		}
	}

	// Input text file into array
	for(;;) {
		// LOOP INVARIANT: The file has not ended

		j = i;
		i = fgetc(file);

		// Is the file over?
		if (feof(file)) {
			// End the loop
			break;
		}

        // Is it a newline character?
		if (i == '\n') {
			// It is a newline character

			// Was last char newline
			if (j == '\n') {
				// Yes
				break;
			}
			a++;
			b = 0;
		}
		else {
			// Is it an x?
			if(i == 'x') {
				// It is an x
				array[a][b] = 'x';
			}
			else {
				// It is not an x
				array[a][b] = ' ';
			}
			b++;
		}
	}
	return array;
}

/** Find width of FILE
 * @param file The file to be measured
 * @return The width of the longest line in the file
 */
int fileWidth(FILE* file) {

	int max = 0;                            // longest line so far
	int count = 0;                          // character count for an individual line
	char i = ' ';                              // current character in the file

	// Count the length of each line and find the greatest
	for(;;) {
		// LOOP INVARIANT: The file has not ended

		i = fgetc(file);

		// Is the file over?
		if (feof(file)) {
			// End the loop

			// See if count is greater than max
			if(max < count) {
				// Set a new max
				max = count;
			}
			count = 0;

			break;
		}

		// Is this a newline character?
		if(i == '\n') {
			// Line is over; set new max; reset count

			// See if count is greater than max
			if(max < count) {
				// Set a new max
				max = count;
			}
			count = 0;
		}
		else {
			count++;
		}
	}
	return max;
}

/** Find height of FILE
 * @param file The file to be measured
 * @return The number of line in the file
 */
int fileHeight(FILE* file) {

	int count = 0;                          // character count for an individual line
	char i = ' ';                           // current character in the file
	char j = ' ';                           // previous character

	// Count each line
	for(;;) {
		// LOOP INVARIANT: The file has not ended

		j = i;
		i = fgetc(file);

		// Is the file over?
		if (feof(file)) {
			// End the loop

			// Was last char newline
			if(j != '\n') {
				// No
				count++;
			}
			break;
		}

		// Is this a newline character?
		if(i == '\n' && j != '\n') {
			// It is a new line character
			count++;
		}
	}
	return count;
}
