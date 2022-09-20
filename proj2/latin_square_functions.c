/******************************************************************************
 * @file: latin_square_functions.c
 *
 * WISC NETID
 * CANVAS USERNAME
 * WISC ID NUMBER
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: YOUR PREFERED NAME (YOUR WISC EMAIL)
 * @modified: SUBMISSION DATE
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
    /* BEGIN MODIFYING CODE HERE */
	
	// this section opens, reads, and determines the dimensions of the latin square (n)
	size_t count = 0;
	FILE *fileIn = fopen(filename, "r"); // opens file
	int c = fgetc(fileIn);
	while(c != '\n'){ // reads file
		count++; // increments n for each newline char found
		c = fgetc(fileIn);
	}
	*n = count;
	
	// this section reserves memory and then stores the input file data in that memory before closing the file
	*latin_square_in = malloc(*n*sizeof(char*)); // reserves array of pointers to rows
	for(int i = 0; i < *n; i++)
		*(*latin_square_in + i) = malloc(*n * sizeof(char*)); // reserves array of chars in each row
	rewind(fileIn); // takes us back to fileIn start to begin filling in data
	for(int row = 0; row < *n; row++){
		for(int col = 0; col < *n + 1; col++){
			char character = fgetc(fileIn); // store next char in character
			if(character == '\n'){ // make sure char to be placed in latin square is valid
				continue;
			}
			*(*(*latin_square_in + row) + col) = character; // fill in latin square
		}
	}
	
	fclose(fileIn);
	
    /* END MODIFYING CODE HERE */
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
	
	int *count = malloc(128 * sizeof(int));
	for(int i = 0; i < 128; i++)
		*(count + i) = 0;
		
	for(int i = 0; i < n; i++){ // iterate through each row of latin_square
		for(int j = 0; j < n; j++){ // iterate through each char in each row of latin_square
			*(count + *(*(latin_square + i) + j)) += 1;
		}
	}
	
	for(int i = 0; i < 128; i++){
		if(*(count + i) != 0 && *(count + i) != n){
			free(count);
			return 0;
		}
	}

	free(count);
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
	int check = 1;
	int *count = malloc(128*sizeof(int));
	for(int i = 0; i < 128; i++)
		*(count + i) = 0;
	
	// checks for dupes in rows
	for(int r = 0; r < n; r++){
		for(int c = 0; c < n; c++){
			if(*(count + *(*(latin_square + r) + c)) == 1){
				printf("Error in column %d\n", c);
				check = 0;
			}
			else
				*(count + *(*(latin_square + r) + c)) += 1;
		}
		for(int i = 0; i < 128; i++)
			*(count + i) = 0;
	}
	// checks for dupes in columns
	for(int r = 0; r < n; r++){
		for(int c = 0; c < n; c++){
			if(*(count + *(*(latin_square + c) + r)) == 1){
				printf("Error in row %d\n", r);
				check = 0;
			}
			else
				*(count + *(*(latin_square + c) + r)) += 1;
		}
		for(int i = 0; i < 128; i++)
			*(count + i) = 0;
	}
	
	free(count);
	return check;
	/* END MODIFYING CODE HERE */
    // return 1;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    /* BEGIN MODIFYING CODE HERE */
	
	for(int i = 0; i < n; i++){
		free(*(latin_square + i));
	}
	free(latin_square);
	
    /* END MODIFYING CODE HERE */
}


