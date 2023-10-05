#define _POSIX_C_SOURCE 200809L
#define MAX_LINE 127

#include "pirate.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


pirate *pirate_create(){
    pirate *new = malloc(sizeof(pirate));
    if (new == NULL) {
        fprintf(stderr, "MemoryError: No memory\n");
        exit(1);
    }
    
    strcpy(new->name, "N/A");
    new->vessel = strdup("N/A");
    new->captain = strdup("N/A");
    new->num_treasure = 0;
    new->fav_port = strdup("N/A");
    new->skill = NULL;
    new->num_skills = 0;
    return new;
}

pirate *pirate_read(FILE *input){
    char line[MAX_LINE];
    // Check if it is at the end of the file
    if (fgets(line, sizeof(line), input) == NULL) {
        return NULL;
    }
    pirate *curr_pirate = pirate_create();
    char *extraline = strchr(line, '\n');
    if (extraline) {
        *extraline = '\0';
    }
    // free(curr_pirate->name);
    // curr_pirate->name = strdup(name);
    strncpy(curr_pirate->name, line, MAX_LINE);
    curr_pirate->name[MAX_LINE] = '\0';

    // This is where the extra functionality for PSET3 comes in
    // You would have to use realloc for skills to add different skillsets
    // Consume the blank line after the profile.
    fgets(line, sizeof(line), input);
    return curr_pirate;
}

void pirate_print(const pirate *p, FILE *output){
    fprintf(output, "%s\n", pirate_name(p));
    // For next assignment
    // fprintf(output, "    Vessel: %s\n", p->vessel);
    // fprintf(output, "    Captain: %s\n", p->captain);
    // fprintf(output, "    Treasure: %s\n", p->num_treasure);
    // fprintf(output, "    Port: %s\n", p->fav_port);
    // fprintf(output, "    Skill: %s\n", p->skill);
}


const char *pirate_name(const pirate *p){
    return p->name;
}

void pirate_set_name(pirate *p, const char *name){
    // free(p->name);
    // p->name = strdup(name);
    strncpy(p->name, name, MAX_LINE);
    p->name[MAX_LINE] = '\0';  
}

int pirate_compare(pirate *a, pirate *b){
    const char* name1 = pirate_name(a);
    const char* name2 = pirate_name(b);
    int len = strlen(name1);
    for (int i=0; i<len; i++){
        if (name1[i] > name2[i]) {
            return 1;
        } else if (name1[i] <  name2[i]) {
            return -1;
        }
    }
    return 0;
}

void pirate_destroy(pirate *p){
    // free(p->name);
    free(p->vessel);
    free(p->captain);
    free(p->fav_port);
    for (int i = 0; i < p->num_skills; i++) {
        free(p->skill[i]);
    }
    free(p->skill);
    free(p);
}

