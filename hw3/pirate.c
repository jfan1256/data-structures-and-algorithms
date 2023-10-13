#define _POSIX_C_SOURCE 200809L
#define MAX_LINE 127

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "pirate.h"


pirate *pirate_create(void){
    pirate *new = malloc(sizeof(pirate));
    if (new == NULL) {
        fprintf(stderr, "MemoryError: No memory\n");
        exit(1);
    }
    
    strcpy(new->name, "N/A");
    strcpy(new->vessel, "N/A");
    strcpy(new->rank, "N/A");
    new->captain = NULL;
    strcpy(new->port, "N/A");
    new->treasure = -1;
    new->skill = skills_list_create();
    return new;
}

pirate *pirate_read(FILE *restrict input){
    char line[MAX_LINE];
    // Check if it is at the end of the file
    if (fgets(line, sizeof(line), input) == NULL){
        return NULL;
    }

    pirate *curr_pirate = pirate_create();
    char *extraline = strchr(line, '\n');
    if (extraline) {
        *extraline = '\0';
    }

    pirate_set_name(curr_pirate, line);

    // Consume the blank line after the profile or continues to read the added items
    while (fgets(line, sizeof(line), input) && strlen(line) != 1){
        // Trim newline
        extraline = strchr(line, '\n');
        if (extraline) {
            *extraline = '\0';
        }

        // Add respective attributes
        char *colon = strchr(line, ':');
        if (colon && *(colon + 1)) {
            char *value = colon + 1;
            if (strstr(line, "port:")){
                pirate_set_port(curr_pirate, value);
            } else if (strstr(line, "rank:")){
                pirate_set_rank(curr_pirate, value);
            } else if (strstr(line, "vessel:")){
                pirate_set_vessel(curr_pirate, value);
            } else if (strstr(line, "skill:")){
                skills_list_append(curr_pirate->skill, value);
            } else if (strstr(line, "treasure:")){
                pirate_set_treasure(curr_pirate, strtoul(value, NULL, 10));
            }
        }
    }
    return curr_pirate;
}

void print_rating(bool *header, FILE *output, char *skill, int rating){
    // Print the header only once
    if (!*header) {
        fprintf(output, "    Skill: ");
        *header = true;
    } else {
        fprintf(output, "           ");
    }

    // Print the skill and its rating
    fprintf(output, "%s ", skill);
    for (int j = 0; j < rating - 1; j++){
        fprintf(output, "*");
    }
    fprintf(output, "\n");
}

void pirate_print(const pirate *p, FILE *output){
    fprintf(output, "%s\n", pirate_name(p));
    if (pirate_captain(p) != NULL){
        fprintf(output, "    Captain: %s (%s)\n", pirate_name(pirate_captain(p)), pirate_vessel(pirate_captain(p)));
    }
    if (strcmp(pirate_rank(p), "N/A") != 0){
        fprintf(output, "    Rank: %s\n", pirate_rank(p));
    }
    if (strcmp(pirate_vessel(p), "N/A") != 0){
        fprintf(output, "    Vessel: %s\n", pirate_vessel(p));
    }
    if (strcmp(pirate_port(p), "N/A") != 0){
        fprintf(output, "    Port: %s\n", pirate_port(p));
    }
    if (pirate_treasure(p) != -1){
        fprintf(output, "    Treasure: %d\n", pirate_treasure(p));
    }
     if (pirate_skills(p) != NULL) {
        bool header = false;

        for (int i = 0; i < skills_list_len(pirate_skills(p));) {
            char *current_skill = skills_list_get(pirate_skills(p), i);
            int rating = 1;

            // Count duplicates of the current skill
            while (i + rating < skills_list_len(pirate_skills(p)) && strcmp(current_skill, skills_list_get(pirate_skills(p), i + rating)) == 0) {
                rating++;
            }

            // Print the skill and its rating
            print_rating(&header, output, current_skill, rating);
            
            // Move to the next skill that is different from the current one
            i += rating;
        }
    }
}

const char *pirate_name(const pirate *p){
    return p->name;
}

void pirate_set_name(pirate *p, const char *name){
    strncpy(p->name, name, MAX_LINE);
    p->name[MAX_LINE] = '\0';  
}

const char *pirate_vessel(const pirate *p){
    return p->vessel;
}

void pirate_set_vessel(pirate *p, const char *vessel){
    strncpy(p->vessel, vessel, MAX_LINE);
    p->vessel[MAX_LINE] = '\0';  
}

const char *pirate_port(const pirate *p){
    return p->port;
}

void pirate_set_port(pirate *p, const char *port){
    strncpy(p->port, port, MAX_LINE);
    p->port[MAX_LINE] = '\0';  
}

const char *pirate_rank(const pirate *p){
    return p->rank;
}

void pirate_set_rank(pirate *p, const char *rank){
    strncpy(p->rank, rank, MAX_LINE);
    p->rank[MAX_LINE] = '\0'; 
}

unsigned int pirate_treasure(const pirate *p){
    return p->treasure;
}

void pirate_set_treasure(pirate *p, unsigned int treasure){
    p->treasure = treasure;
}

const pirate *pirate_captain(const pirate *p){
    return p->captain;
}

void pirate_set_captain(pirate *p, const pirate *cpt){
    p->captain = cpt;
}

skills_list *pirate_skills(const pirate *p){
    return p->skill;
}

void pirate_destroy(pirate *p){
    skills_list_destroy(pirate_skills(p));
    free(p);
}

