#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include <stdio.h>

/**
 * Append pirates to pirate_list from input file and sort it
*/
void organize(FILE *input, pirate_list *pirates){
    while(1){
        pirate *curr_pirate = pirate_read(input);
        if (curr_pirate == NULL) {
            // Reached the end of the file
            break;
        }
        // Append curr_pirate only if it is not in the pirate_list
        if (list_index_of(pirates, curr_pirate) == list_length(pirates))
            append(pirates, curr_pirate);
    }
    list_sort(pirates);
}

/**
 * Print the pirates in pirate_collection
*/
void print_pirates(pirate_list *pirates){
    size_t len = list_length(pirates);
    for (size_t i = 0; i < len; i++){
        pirate_print(list_access(pirates, i), stdout);
    }
}