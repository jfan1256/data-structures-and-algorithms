#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

#include <stdio.h>
#include <stdbool.h>
#include "pirate_list.h"
#include "pirate.h"

/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h or pirate_list.h.

Author: [Jonathan Fan]
*/

/**
 * Checks if a file is valid or not
*/
bool is_valid_file(const char* filename);

/**
 * Creates the pirate list from input file and sorts it
*/
void organize(FILE *input, pirate_list *pirates);

/**
 * Print the pirates in pirate_collection
*/
void print_pirates(pirate_list *pirates);

#endif