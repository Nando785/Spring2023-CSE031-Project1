#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wsFunctions.c"

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void capsAll(char* word);
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void hasNeighbor(char** arr, char* word, int row, int column);
void printResult();
int bSize, letterIndex = 0, lastFound = 0, notFinished = 1;
struct Stack* storage;

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

void printPuzzle(char** arr) {
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

void capsAll(char* word){ // capitalize all letters in word
    char* loc = word;
    while(*loc != '\0'){
        if(*loc >= 'a' && *loc <= 'z'){ // check if lower case letter
            *loc = *loc - 32; // capitalize letters (subtract 32 from ASCII value)
        }
        loc++;
    }
}

void printResult(){ // print the search path
    printf("\nPrinting the search path:\n");
    char ***finalArray = (char***)malloc(bSize * sizeof(char**));

    for(int row = 0; row < bSize; row++){ // initialize finalArray, all indexes must contain "0"
        *(finalArray + row) = (char**)malloc(bSize * sizeof(char*));
        for(int column = 0; column < bSize; column++){
            *(*(finalArray+row)+column) = (char*)malloc(2 * sizeof(char)); // Allocate space for two characters (1 for digit, 1 for null terminator)
            *(*(finalArray+row)+column) = "0";
        }
    }

    int iterator = storage->nodeCount+1;
    char* num = (char*)malloc(2*sizeof(char));
    while(storage->top != NULL){
        struct node* temp = storage->top;
        char* temp_str = *(*(finalArray + temp->i) + temp->j);

        sprintf(num, "%d", iterator); // copy location number 

        if(strcmp(temp_str, "0") == 0){ // if character at location is 0
            *(*(finalArray + temp->i) + temp->j) = malloc(strlen(num) + 1); // allocate memeory for num
            strcpy(*(*(finalArray + temp->i) + temp->j), num); // insert iterator
        } else {
            char* concatenated = (char*)malloc(strlen(temp_str) + strlen(num) + 1); // allocate memory for current string and number to be added
            strcpy(concatenated, temp_str); // copy current string
            strcat(concatenated, num); // attach number to index
            *(*(finalArray + temp->i) + temp->j) = concatenated; // insert into finalArray
        }       

        iterator--;
        pop(storage);
    }

    for(int row = 0; row < bSize-1; row++){ // print finalArray
        for(int col = 0; col < bSize; col++){
            printf("%s\t", *(*(finalArray + row) + col));
        }
        printf("\n");
    }

    for(int row = 0; row < bSize; row++){// print array's last row
        printf("%s\t", *(*(finalArray + bSize-1) + row));
    }
}

void searchPuzzle(char** arr, char* word) {
    storage = createStack();
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    capsAll(word); // make all letters caps
    const char currentLetter = *word; // get first letter of word

    for(int row = 0; row < bSize; row++){ // loop through 2D array
        for(int column = 0; column < bSize; column++){ // loop through 2D array

            if(*(*(arr + row) + column) == currentLetter){ // check if located first letter
                struct node loc = {row, column}; // make a copy of current location
                push(storage, &loc); // save current location to stack
                letterIndex++;
                hasNeighbor(arr, word, row, column); // search for further letters

                if(lastFound){ // if backtracing returns to start, remove original call location
                    while(storage->top != NULL){
                        pop(storage);
                    }
                    lastFound = 0; // reset for next search
                }
            }
        }
    }
    printf("\n");
    if(notFinished){ // if not found, notify
        printf("Word not found\n");
    }

    destroyStack(storage); // free stack memory
}

void hasNeighbor(char** arr, char* word, int row, int column){ // search indexes around [row,column] for next letter
    if(!notFinished){ // If word already found, just return
        return;
    }
    
    int limit = 8, searched = 0; // set default surrounding indices to 8, searched surroindings to none
    if(*(word+letterIndex) == '\0'){ // exit once we have reached the end of the word // base case
        printf("\nWord found!");
        printResult(&storage);
        notFinished = 0; // don't recuerively call anymore
        return;
    }

    if(row == 0 || row == bSize-1 || column == 0 || column == bSize-1){ // check if on edges
        limit = 5; // if on edge, max 5 possible surrounding indexes
        if((row == 0 && column == bSize-1) || (row == bSize-1 && column == 0) || (row == 0 && column == 0) || (row == bSize-1 && column == bSize-1)){ // check if corner
            limit = 3; // if on corner, max 3 possible surrounding indexes
        }
    }

    for(int i = row - 1; i <= row + 1; i++){ // search surrounding rows
        for(int j = column - 1; j <= column + 1; j++){ // search surrounding columns
            if( !(i < 0) && !( i > bSize-1) && !(j < 0) && !(j > bSize-1) ){ // check if valid index
                if(!(i == row && j == column)){ // avoid current location
                    searched++; // increase search counter
                    if(*(*(arr + i) + j) == *(word+letterIndex)){ // if index contains letter
                        struct node loc = {i, j};
                        push(storage, &loc);
                        letterIndex++; // increment for next letter
                        hasNeighbor(arr, word, i, j); // search for next letter
                    }
                }
            }
        }
    }

    if(searched == limit){ // if all surrounding indexes have been searched, remove index
        letterIndex--;
        pop(storage);
        lastFound = 1;
        return;
    }
}