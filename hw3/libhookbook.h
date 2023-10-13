#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

#include <stdio.h>
#include <stdbool.h>
#include "pirate.h"
#include "pirate_list.h"

/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h or pirate_list.h.

Author: [Jonathan Fan]
Modified by: [Jonathan Fan] on [10/13/2023]
Changelog: [Added: All the required functionalities for libhookbook]
*/

/**
 * Checks if a file is valid or not
*/
bool is_valid_file(const char* filename);

/**
 * Creates the pirate list from input file, sets the captains, and sorts it
*/
void organize(FILE *restrict pirate_file, FILE *restrict captain_file, pirate_list *pirates);

/**
 * Print the pirates in pirate_collection
*/
void print_pirates(pirate_list *pirates);

#endif