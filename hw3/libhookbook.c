#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "libhookbook.h"
#include "pirate.h"
#include "pirate_list.h"

/**
 * Checks if a file is valid or not
*/
bool is_valid_file(const char* filename) {
    // File does not exit or cannot be opened
    FILE *file = fopen(filename, "r");
    if (!file) {
        return false;  
    }
    // File properties are invalid
    struct stat st;
    if (stat(filename, &st) != 0) {
        fclose(file);
        return false;
    }
    // File is empty
    if (st.st_size == 0) {
        fclose(file);
        return false;  
    }
    // File is valid
    fclose(file);
    return true;
}


/**
 * Append pirates to pirate_list from input file and sort it
*/
void organize(FILE *restrict pirate_file, FILE *restrict captain_file, pirate_list *pirates){
    while(1){
        pirate *curr_pirate = pirate_read(pirate_file);
        if (curr_pirate == NULL) {
            // Reached the end of the file
            break;
        }
        // Append curr_pirate only if it is not in the pirate_list --> this ensures no duplicates and only the first instance is stored
        if (list_index_of(pirates, curr_pirate) == list_length(pirates)){
            append(pirates, curr_pirate);
        } else {
            pirate_destroy(curr_pirate);
        } 
    }

    // Read captain file and set captains
    pirate_read_captain(captain_file, pirates);

    // Sort the list
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