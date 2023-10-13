#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"

int main(int argc, char* argv[]) {
    // Handle error cases and reading in arguments from compiler
    const char* pirate_file = NULL;
    const char* captain_file = NULL;
    char flag = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-'){
            // Argument is a flag
            if (flag != 0){
                // Flag has already been assigned, but another argument is also a flag --> Throw error
                fprintf(stderr, "cannot have multiple flag arguments in compiler\n");
                exit(1);
            }
            if (strlen(argv[i]) != 2 || (argv[i][1] != 'n' && argv[i][1] != 'v' && argv[i][1] != 't')) {
                // Flag is not one of the three options --> Throw an error
                fprintf(stderr, "invalid flag types: can only use -n, -v, or -t\n");
                exit(1);
            } 
            // Assign flag to arguement flag
            flag = argv[i][1];
        } else {
            // It is a filename
            if (pirate_file == NULL) {
                // If pirate_file is NULL --> assign; This ensures that it follows order as this if statement comes before conditional statement for captain_file
                pirate_file = argv[i];
            } else if (captain_file == NULL) {
                // If captain_file is NULL --> assign
                captain_file = argv[i];
            } else {
                fprintf(stderr, "too many files passed\n");
                exit(1);
            }
        }
    }

    // If either pirate_file or captain_file is NULL, then program cannot run
    if (pirate_file == NULL || captain_file == NULL) {
        fprintf(stderr, "Not enough files passed\n");
        exit(1);
    }

    // Checks for invalid files (i.e., empty files, n/a files, etc.)
    if (!is_valid_file(pirate_file)) {
        fprintf(stderr, "pirate file is invalid or empty\n");
        exit(1);
    }

    // Initalize file to read
    FILE *input_pirate = fopen(pirate_file, "r");
    FILE *input_captain = fopen(captain_file, "r");

    // Allocate memory for all_pirates
    int (*comp)(const void*, const void*) = determine_comp(flag);
    pirate_list *all_pirates = list_create(comp);

    // Append pirates and sort all_pirates
    organize(input_pirate, input_captain, all_pirates);

    // Print pirates
    print_pirates(all_pirates);

    // Free pirate and close input file
    list_destroy(all_pirates);
    fclose(input_pirate);
    fclose(input_captain);
    return 0;
}