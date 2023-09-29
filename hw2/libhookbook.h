#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

#include "pirate_list.h"
#include "pirate.h"
#include <stdio.h>

/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h or pirate_list.h.

Author: [Jonathan Fan]
*/

/**
 * Creates the pirate list from input file and sorts it
*/
void organize(FILE *input, pirate_list *pirates);

/**
 * Print the pirates in pirate_collection
*/
void print_pirates(pirate_list *pirates);

#endif