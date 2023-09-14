#ifndef SIZE
#define SIZE 10
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "life.h"

int main(int argc, char* argv[]) {
    // Throw an error if not enough parameters or too many
    if (argc != 3) {
        fprintf(stderr, "ArgumentError: Must have 3 arguments\n");
        exit(1);
    }

    // Initalize variables
    int time_step = atoi(argv[1]);
    char* init = argv[2];
    size_t len = strlen(init);
    static int cell[SIZE];

    // Check if time_step is negative
    if (time_step < 0) {
        fprintf(stderr, "ValueError: Number of simulation steps cannot be negative.\n");
        exit(1);
    }

    // Check if equal to size
    if (len != SIZE){
        fprintf(stderr, "ValueError: Size is incorrect. It must have %d cells.\n", SIZE);
        exit(1);
    }

    // Create life array and see if any values are not 0 or 1
    for (int i = 0; i < len; i++){
        cell[i]=init[i] - '0';
        if (cell[i] != 1 && cell[i] != 0){
            fprintf(stderr, "ValueError: Values can only be 0 or 1.\n");
            exit(1);
        }
    }

    // Output initial step
    output(cell, 0, len);

    // Iterate through steps in simulaion
    for (int i = 1; i < time_step+1; i++){
        static int alter_cell[SIZE];
        int* altered = alter(cell, alter_cell, len);
        
        // Copy altered cells to current cell state
        for(int k = 0; k < len; k++) {
            cell[k] = altered[k];
        }

        output(altered, i, len);
    }
        
    return 0;
}