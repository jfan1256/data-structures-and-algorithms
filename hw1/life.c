#include "life.h"
#include <stdbool.h>
#include <stdio.h>
#include "helpers.h"

// Checks if cell is alive or not
bool isAlive(int field[], size_t i, size_t size) {
    if (field[i]==1){
        return true;
    } else {
        return false;
    }
}

// Determines if cell should die or not
bool shouldDie(int field[], size_t i, size_t size){
    if (field[i+1]==1 && field[i-1]){
        return true;
    } else {
        return false;
    }
}   

// Performs the simulation
int* alter(int field[], int new[], size_t size){
    // Initalize new array with starting and ending value equal to field
    new[0] = field[0];
    new[size-1] = field[size-1];

    for (int j=0; j < size; j++){

        if (j == 0){
            // Edge case on the leftmost cell
            if (isAlive(field, j, size) == true && isAlive(field, j+1, size) == false){
                new[j+1] = 1;
            }
        } else if (j == size-1) {
            // Edge case on the rightmost cell
            if (isAlive(field, j, size) == true && isAlive(field, j-1, size) == false){
                new[j-1] = 1;
            }
        } else if (isAlive(field, j, size) == true && shouldDie(field, j, size) == true){
            // If cell is alive and has two neighboring live cells
            new[j] = 0;
        } else if (isAlive(field, j, size) == true && shouldDie(field, j, size) == false){
            // If cell is alive and does not have two neighboring live cells
            // Check all cases
            new[j] = 1;
            if (field[j-1] == 1){
                // If left cell is alive then right cell must be dead
                new[j+1] = 1;
            } else if (field[j+1] == 1) {
                // If right cell is alive then left cell must be dead
                new[j-1] = 1;
            } else {
                // Both are dead
                new[j-1] = 1;
                new[j+1] = 1;
            }
        }
    }
    return new;
} 

