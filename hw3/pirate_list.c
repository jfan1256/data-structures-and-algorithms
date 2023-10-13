#define _POSIX_C_SOURCE 200809L
#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pirate_list.h"
#include "pirate.h"

struct pirate_list_instance_t{
    pirate **pirate_collection;
    int (*comp)(const void *, const void *);
    size_t length;
    size_t capacity;
};

int comp_by_name(const void *a, const void *b){
    const pirate *pirate_a = (const pirate *)a;
    const pirate *pirate_b = (const pirate *)b;
    return strcmp(pirate_name(pirate_a), pirate_name(pirate_b));
    
}

int comp_by_vessel(const void *a, const void *b){
    const pirate *pirate_a = (const pirate *)a;
    const pirate *pirate_b = (const pirate *)b;

    const char* vessel_a = pirate_vessel(pirate_a);
    const char* vessel_b = pirate_vessel(pirate_b);

    // Check if either pirate has a vessel of "N/A"
    if (strcmp(vessel_a, "N/A") == 0 && strcmp(vessel_b, "N/A") == 0) {
        return comp_by_name(a, b);
    } else if (strcmp(vessel_a, "N/A") == 0) {
        return 1;
    } else if (strcmp(vessel_b, "N/A") == 0) {
        return -1;
    }

    return strcmp(vessel_a, vessel_b);
}

int comp_by_treasure(const void *a, const void *b){
    const pirate *pirate_a = (const pirate *)a;
    const pirate *pirate_b = (const pirate *)b;
    
    int treasure_a = pirate_treasure(pirate_a);
    int treasure_b = pirate_treasure(pirate_b);

    // Check if either pirate has a treasure of -1
    if (treasure_a == -1 && treasure_b == -1) {
        return comp_by_name(a, b);
    } else if (treasure_a == -1) {
        return 1;
    } else if (treasure_b == -1) {
        return -1;
    }

    return treasure_b - treasure_a;
}

int (*determine_comp(char flag))(const void*, const void*) {
    switch(flag) {
    case 'n':
        return comp_by_name;
    case 'v':
        return comp_by_vessel;
    case 't':
        return comp_by_treasure;
    default:
        return comp_by_name;
    }
}


pirate_list *list_create(int (*comp)(const void*, const void*)){
    pirate_list *new = malloc(sizeof(pirate_list));
    if (new == NULL) {
        fprintf(stderr, "MemoryError: No memory\n");
        exit(1);
    }
    new->pirate_collection = malloc(INITIAL_CAPACITY * sizeof(pirate*));
    if (new->pirate_collection == NULL){
        fprintf(stderr, "MemoryError: No memory\n");
        exit(1);
    }

    new->comp = comp;
    new->length = 0;
    new->capacity = INITIAL_CAPACITY;
    return new;
}

size_t list_index_of(pirate_list *pirates, pirate *p){
    for (size_t i = 0; i < list_length(pirates); i++){
        if (comp_by_name(pirates->pirate_collection[i], p) == 0){
            return i; 
        }
    }
    return list_length(pirates);
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx){
    list_expand_if_necessary(pirates);
    size_t pirate_idx = list_index_of(pirates, p);
    // Shift everything to the right
    if (pirate_idx == list_length(pirates)){
        for (size_t j = pirates->length; j > idx; j--){
            pirates->pirate_collection[j+1] = pirates->pirate_collection[j];
        }
        pirates->pirate_collection[idx] = p;
        // Add 1 to length of pirate collection
        pirates->length++;
        return NULL;
    } else {
        return p;
    }
}

pirate *list_remove(pirate_list *pirates, pirate *p){
    size_t idx = list_index_of(pirates, p);
    // If pirate not in list
    if (idx == list_length(pirates)){
        return NULL;
    }

    pirate *removed_pirate = pirates->pirate_collection[idx];

    // Shift everything to the left
    for (size_t j = idx; j < pirates->length - 1; j++){
        pirates->pirate_collection[j] = pirates->pirate_collection[j + 1];
    }
    // Subtract 1 from length of pirate collection and nullify the last index
    pirates->pirate_collection[pirates->length - 1] = NULL;
    pirates->length--;
    list_contract_if_necessary(pirates);
    return removed_pirate;
}

pirate *list_access(pirate_list *pirates, size_t idx){
    if (idx >= list_length(pirates)){
        return NULL;
    }
    return pirates->pirate_collection[idx];
}

pirate* get_pirate_by_name(pirate_list *pirates, char *name){
    for (size_t i = 0; i < list_length(pirates); i++){
        if (strcmp(pirates->pirate_collection[i]->name, name) == 0){
            return pirates->pirate_collection[i];
        }
    }
    return NULL;
}

void pirate_read_captain(FILE *restrict input, pirate_list *pirates){
    char line1[MAX_LINE];
    char line2[MAX_LINE];

    while (fgets(line1, sizeof(line1), input) && fgets(line2, sizeof(line2), input)){
        // Read in two lines at a time and trim the newline character at end
        line1[strcspn(line1, "\n")] = 0;
        line2[strcspn(line2, "\n")] = 0;  
        // Set captain
        pirate *pirate1 = get_pirate_by_name(pirates, line1);
        pirate *pirate2 = get_pirate_by_name(pirates, line2);

        // Check if pirate1 and pirate2 are valid
        if (pirate1 && pirate2){  
            size_t index1 = list_index_of(pirates, pirate1);
            size_t index2 = list_index_of(pirates, pirate2);

            pirate_set_captain(list_access(pirates, index1), list_access(pirates, index2));
        } else {
            fprintf(stderr, "invalid captain file: pirates do not exist in pirate_list\n");
            exit(1);
        }
    }
}

void list_sort(pirate_list *pirates){
    size_t left = 0;
    size_t right = list_length(pirates)-1;
    index(pirates, left, right);
}

// Sets the indices for merging
void index(pirate_list *pirates, size_t left, size_t right){
    if (left < right) {
        // Overflow issue
        size_t middle = left + (right-left) / 2;
        index(pirates, left, middle);
        index(pirates, middle+1, right);
        merge(pirates, left, middle, right);
    }
}

/*
If comp_treasure or comp_vessel return 0 (meaning the two comparisons are equal), then sort by name
*/
int secure_comp_func(const void *a, const void *b, int (*comp_func)(const void *, const void *)){
    int prim_comp = comp_func(a, b);
    if (prim_comp == 0) {
        return comp_by_name(a, b);
    }
    return prim_comp;
}

/*
The merging algorithm for inplace-merge sort
*/
void merge(pirate_list *pirates, size_t start_left, size_t middle, size_t end_right){
    int (*comp_func)(const void *, const void *) = pirates->comp;

    size_t start_right = middle + 1;
    // If the last name of the first list is equal or comes before the first name in the second list, then everything is already sorted
    if (secure_comp_func(list_access(pirates, middle), list_access(pirates, start_right), comp_func) <= 0){
        return;
    }
    // Begin merging algorithm is sorting is required
    while (start_left <= middle && start_right <= end_right){
        // If the first name of the first list is before the first name of the second list, move the pointer right
        if (secure_comp_func(list_access(pirates, start_left), list_access(pirates, start_right), comp_func) <= 0){
            start_left++;
        } else {
            // Insert name in second list that comes before name in first list
            pirate *pirate_to_add = list_access(pirates, start_right); 
            size_t track = start_right;
            while (track != start_left) {
                pirates->pirate_collection[track] = pirates->pirate_collection[track-1];
                track--;
            }
            pirates->pirate_collection[start_left] = pirate_to_add;
            start_left++;
            middle++;
            start_right++;
        }
    }
}

size_t list_length(pirate_list *pirates){
    return pirates->length;
}

void list_destroy(pirate_list *pirates){
    for (size_t i = 0; i < pirates->length; i++){
        pirate_destroy(pirates->pirate_collection[i]);
    }
    free(pirates->pirate_collection);
    free(pirates);
}

void list_expand_if_necessary(pirate_list *pirates){
    if (list_length(pirates) == pirates->capacity){
        size_t new_capacity = pirates->capacity * RESIZE_FACTOR;
        pirate** expand_colection = realloc(pirates->pirate_collection, new_capacity * sizeof(pirate*));
        if (expand_colection == NULL) {
            fprintf(stderr, "MemoryError: Cannot expand the pirate collection.\n");
            exit(1);
        }
        pirates->pirate_collection = expand_colection;
        pirates->capacity = new_capacity;
        fprintf(stdout, "Expand to %zu\n", new_capacity);
    }
}

void list_contract_if_necessary(pirate_list *pirates){
    if (list_length(pirates) <= pirates->capacity/4 && pirates->capacity/RESIZE_FACTOR > 25){
        size_t new_capacity = pirates->capacity / RESIZE_FACTOR;
        pirate** contract_collection = realloc(pirates->pirate_collection, new_capacity * sizeof(pirate*));
        if (contract_collection == NULL) {
            fprintf(stderr, "MemoryError: Cannot contract the pirate list.\n");
            exit(1);
        }
        pirates->pirate_collection = contract_collection;
        pirates->capacity = new_capacity;
        fprintf(stdout, "Contract to %zu\n", new_capacity);
    }
}
// Append all pirates
void append(pirate_list *pirates, pirate *p){
    // Expand the collection if necessary
    list_expand_if_necessary(pirates);
    // Append the pirate
    pirates->pirate_collection[pirates->length] = p;
    pirates->length++;
}



