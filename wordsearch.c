#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
void capsAll(char* word);
void hasNeighbor(char** arr, char* word, int letterIndex, int row, int column);

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
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

void searchPuzzle(char** arr, char* word) { // +++++ COMPLETED ? +++++
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
                hasNeighbor(arr, word, 0, row, column); // search for further letters

            }

        }
    }
}

void hasNeighbor(char** arr, char* word, int letterIndex, int row, int column){
// ===== vertical and horizontal comparisons =====
    if(row != bSize-1){ // check if located on right column
        if(*(*(arr + row + 1) + column) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row + 1, column); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row + 1, column); // search for next letter
        }
    }
    
    if(row != 0){ // check if located on left column
        if(*(*(arr + row - 1) + column) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row - 1, column); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row - 1, column); // search for next letter
        }
    }

    if(column != bSize-1){ // check if located on bottom row
        if(*(*(arr + row) + column + 1) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row, column + 1); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row, column + 1); // search for next letter
        }
    }
    
    if(column != 0){ // check if located on top row
        if(*(*(arr + row) + column - 1) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row, column - 1); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row, column - 1); // search for next letter
        }
    }

    // ===== Adjacent Comparisons =====
    if(row != 0 && column != 0){ // check top left
        if(*(*(arr + row - 1) + column - 1) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row - 1, column - 1); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row - 1, column - 1); // search for next letter
        }
    }
    
    if(row != bSize-1 && column != 0){ // check top right
        if(*(*(arr + row) + column) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row, column); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row, column); // search for next letter
        }
    }

    if(row != 0 && column != bSize-1){ // check bottom left
        if(*(*(arr + row) + column) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row, column); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row, column); // search for next letter
        }
    }
    
    if(row != bSize-1 && column != bSize-1){ // check bottom right
        if(*(*(arr + row) + column) == *(word+letterIndex)){ // if index contains letter
            printf("Row: %d, Column: %d\n", row, column); // replace with stack push // save index location in stack
            letterIndex++; // increment for next letter
            hasNeighbor(arr, word, letterIndex, row, column); // search for next letter
        }
    }
}