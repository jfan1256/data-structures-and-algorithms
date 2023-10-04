#define _POSIX_C_SOURCE 200809L
#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

#include "pirate_list.h"
#include "pirate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pirate_list_instance_t{
    pirate **pirate_collection;
    size_t length;
    size_t capacity;
};

pirate_list *list_create() {
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
    new->length = 0;
    new->capacity = INITIAL_CAPACITY;
    return new;
}

size_t list_index_of(pirate_list *pirates, pirate *p){
    for (size_t i = 0; i < list_length(pirates); i++){
        if (pirate_identical(pirates->pirate_collection[i], p) == 0){
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
        printf("inside\n");
        for (size_t j = pirates->length; j > idx; j--) {
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
    pirate *removed_pirate = NULL;
    removed_pirate = pirates->pirate_collection[idx];

    // Shift everything to the left
    if (idx < list_length(pirates)){
        for (size_t j = idx; j < pirates->length - 1; j++) {
            pirates->pirate_collection[j] = pirates->pirate_collection[j + 1];
        }
        // Subtract 1 from length of pirate collection and nullify the last index
        pirates->pirate_collection[pirates->length - 1] = NULL;
        pirates->length--;
        list_contract_if_necessary(pirates);
        pirate_destroy(removed_pirate);
        return removed_pirate;
    } else {
        return NULL;
    }
}

pirate *list_access(pirate_list *pirates, size_t idx){
    if (idx >= list_length(pirates)){
        return NULL;
    }
    return pirates->pirate_collection[idx];
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

// The merging algorithm for inplace-merge sort
void merge(pirate_list *pirates, size_t start_left, size_t middle, size_t end_right) {
    size_t start_right = middle + 1;
    // If the last name of the first list is equal or comes before the first name in the second list, then everything is already sorted
    if (pirate_compare(list_access(pirates, middle), list_access(pirates, start_right)) <= 0) {
        return;
    }
    // Begin merging algorithm is sorting is required
    while (start_left <= middle && start_right <= end_right){
        // If the first name of the first list is before the first name of the second list, move the pointer right
        if (pirate_compare(list_access(pirates, start_left), list_access(pirates, start_right)) <= 0){
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

// // The merging algorithm for merge sort
// pirate_list *conquer(pirate_list *to_conquer1, pirate_list *to_conquer2){
//     int index = 0;
//     // Set to_conquer1 as the list the append too (making it O(1))
//     // Repeatedly check if to_conquer2's first element is before, equal, or after to_conquer1
//     while (list_length(to_conquer2) > 0 && index < list_length(to_conquer1)) {
//         pirate *one = list_access(to_conquer1, index);
//         pirate *two = list_access(to_conquer2, 0);

//         int comparison = pirate_compare(one, two);

//         if (comparison == 0){
//             to_conquer1 = list_insert(to_conquer1, two, index);
//             to_conquer2 = list_remove(to_conquer2, two);
//             // Need to add by two because there is an added element
//             index = index + 2;
//         } else if (comparison == 1){
//             to_conquer1 = list_insert(to_conquer1, two, index);
//             to_conquer2 = list_remove(to_conquer2, two);
//             // Need to add by two because there is an added element
//             index = index + 2;
//         } else {
//             // No need to change anything if to_conquer1's element is before to_conquer2's element
//             index++;
//         }
//     }
//     // Add any excess elements of to_conquer2 to the end of to_conquer1
//     while (list_length(to_conquer2) > 0) {
//         pirate *excess = list_access(to_conquer2, 0);
//         to_conquer1 = list_insert(to_conquer1, excess, index+1);
//         to_conquer2 = list_removec(to_conquer2, excess);
//         index++;
//     }
//     return to_conquer1; 
// }


size_t list_length(pirate_list *pirates){
    return pirates->length;
}

void list_destroy(pirate_list *pirates){
    for (size_t i = 0; i < pirates->length; i++) {
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
            // Handle memory allocation failure
            fprintf(stderr, "MemoryError: Cannot contract the pirate list.\n");
            exit(1);  // Or handle the error as appropriate
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



