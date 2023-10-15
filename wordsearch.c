#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void capsAll(char* word);
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void hasNeighbor(char** arr, char* word, int letterIndex, int row, int column, int amountSearched);
void printResult(int stack[]);
int bSize;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) { // +++++ COMPLETED +++++
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for(int row = 0; row < bSize; row++){ // loop through rows
        for(int column = 0; column < bSize; column++){ // loop thorugh columns
            printf("%c ", *(*(arr + row) + column)); // print index
        }
        printf("\n");
    }

}

void capsAll(char* word){ // +++++ COMPLETED +++++

    for(int i = 0; i < 20; i++){
        if(*(word + i) >= 'a' && *(word + i) <= 'z'){ // check if lower case letter
            *(word + i) = *(word + i) - 32; // capitalize letters (subtract 32 from ASCII value)
        }
    }
}

void printResult(int stack[]){

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    capsAll(word); // make all letters caps
    char currentLetter = *word; // get first letter of word

    for(int row = 0; row < bSize; row++){ // loop through 2D array
        for(int column = 0; column < bSize; column++){ // loop through 2D array

            if(*(*(arr + row) + column) == currentLetter){ // check if located first letter
                printf("Row: %d, Column: %d\n", row, column); // replace with stack push // save index location in stack
                hasNeighbor(arr, word, 1, row, column, 1); // search for further letters

            }

        }
    }
}

void hasNeighbor(char** arr, char* word, int letterIndex, int row, int column, int amountSearched){
    if(*(word+letterIndex) == '\0'){ // exit once we have reached the end of the word
        printf("Word found!\n");
        return;
    }

    for(int i = row - 1; i <= row + 1; i++){ // search surrounding rowd
        for(int j = column - 1; j <= column + 1; j++){ // search surrounding columns
            if( !(i < 0) && !( i > bSize-1) && !(j < 0) && !(j > bSize-1) ){ // check if valid index
                if(i != row || j != column){ // avoid current location
                    //printf("Row: %d, Column: %d\n", i, j);

                    if(*(*(arr + i) + j) == *(word+letterIndex)){ // if index contains letter
                        printf("Row: %d, Column: %d\n", i, j); // replace with stack push // save index location in stack
                        letterIndex++; // increment for next letter
                        hasNeighbor(arr, word, letterIndex, i, j, amountSearched++); // search for next letter
                    }else if(row == column){ // if we've reached the last index (no more letters around)
                        // potential issue: amountSearched does not decrease, will delete more than needed
                        // potential fix: pass amountSearched as a reference, make copy for loop, loop and decrement reference by one
                        printf("amountSearched: %d\n", amountSearched);
                        for(int k = 0; k < amountSearched; k++){
                            printf("%d location(s) popped\n", k+1); // replace with stack pop // remove any previously saved indices
                        }
                    }
                }
            }
        }
    }
    return;
}