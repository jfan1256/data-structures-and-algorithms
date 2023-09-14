#include <stdio.h>
#include "helpers.h"
#include "life.h"

int output(int field[], int step, size_t len){
    // Determine whether to print inital or step
    if (step == 0){
        printf("%-16s[ ", "Initial Values");
    } else {
        printf("Step %-10d [ ", step);
    }

    // Loop through array and print values
    for (int i = 0; i < len; i++){
        printf("%d ", field[i]);
        if (i == len-1) {
            printf("]\n");
        }
    }
    return 0;
}
