#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_remove_1(){
    pirate_list* p = list_create();
    pirate* r = pirate_create();
    pirate_set_name(r, "Foo");
    list_insert(p, r, 0);
    pirate* r2 = list_remove(p, r);
    if (list_length(p) == 0)
    {
        printf("test_remove_1 passed!\n");
    }
    else
    {
        printf("test_remove_1 failed!\n");
    }
    pirate_destroy(r2);
    list_destroy(p);
}


int main(int argc, char* argv[]) {
    // Must only have one parameter
    if (argc != 2) {
        fprintf(stderr, "ArgumentError: Must have 1 argument\n");
        exit(1);
    }
    // Initalize file to read
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening file");
        exit(1);
    }
    // Allocate memory for all_pirates
    pirate_list *all_pirates = list_create();
    // Append pirates and sort all_pirates
    organize(input, all_pirates);
    // Print pirates
    print_pirates(all_pirates);
    // Free pirate and close input file
    list_destroy(all_pirates);
    fclose(input);
    return 0;
}