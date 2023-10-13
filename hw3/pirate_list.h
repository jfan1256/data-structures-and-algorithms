#ifndef __PIRATE_LIST_H__
#define __PIRATE_LIST_H__

/*
Header file for pirate list for Hookbook assignments for CPSC 223 Fall 2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is
    already here!
Modified by: [Jonathan Fan] on [10/13/2023]
Changelog: [Added compare, expand, contract, append, and, secure_comp_func functions]
*/

#include <stdlib.h>
#include "pirate.h"

/**
 * Type of a list of pirates, as an opaque struct.
 */
typedef struct pirate_list_instance_t pirate_list;

/**
 * Compare function for name
 */
int comp_by_name(const void *a, const void *b);

/**
 * Compare function for vessel
 */
int comp_by_vessel(const void *a, const void *b);

/**
 * Compare function for treasure
 */
int comp_by_treasure(const void *a, const void *b);

/**
 * Determine the compare function to use from flag provided in terminals
 */
int (*determine_comp(char flag))(const void*, const void*);

/**
 * Allocate memory for a new pirate_list and return a pointer to it.
 *
 * The comparison function returns a negative number, zero, or a positive number
 *  as the first argument "comes before", is the same as, or "comes after" the
 *  second.
 */
pirate_list *list_create(int (*comp)(const void *, const void *));

/**
 * Return the index of the pirate with the same name as p, or a value greater
 *  than or equal to the length of the list if the pirate is not in the list.
 *
 * Ownership of p is not changed.
 */
size_t list_index_of(pirate_list *pirates, pirate *p);

/**
 * Only if there is no pirate in the list with the same name as p, insert
 *  pirate p into the list at index idx by copying the pointer, shifting the
 *  latter part of the list one "slot" to the right.
 *
 * Assumes 0 <= idx <= [the length of the list] (otherwise its behavior is
 *  undefined).
 *
 * If there is a pirate in the list with the same name as p, do nothing, and
 *  return p (the pirate that was not inserted).
 *
 * If the pirate was inserted into the list, return NULL.
 *
 * If p is added to the list, the list claims ownership of the pirate pointed
 *  to by p; otherwise ownership remains with p.
 */
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx);

/**
 * Remove the pirate from the list with the same name as p, and return a
 *  pointer to it.
 * If there is no pirate in the list with the same name as p, return NULL.
 *
 * The caller of this function is responsible for freeing the returned pirate
 *   if it is not NULL.
 */
pirate *list_remove(pirate_list *pirates, pirate *p);

/**
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL
 *  if idx is not a valid index (i.e., it is >= the length of the list).
 *
 * Ownership of the pirate remains with the list.
 */
pirate *list_access(pirate_list *pirates, size_t idx);

/**
 * Get pirate from pirate_list through using a string name
*/
pirate* get_pirate_by_name(pirate_list *pirates, char *name);

/**
 * Reads the captain file and assigns captains to respective pirates
*/
void pirate_read_captain(FILE *restrict input, pirate_list *pirates);

/**
 * Sort the list of pirates according to the order defined when this list was
 * created.
 */
void list_sort(pirate_list *pirates);

/*
If comp_treasure or comp_vessel return 0 (meaning the two comparisons are equal), then sort by name
*/
int secure_comp_func(const void *a, const void *b, int (*comp_func)(const void *, const void *));

/**
 * Sets the indices for merging
*/
void index(pirate_list *pirates, size_t left, size_t right);

/**
 * Merging algorithm for merge sort
*/
void merge(pirate_list *pirates, size_t start_left, size_t middle, size_t end_right);

/**
 * Return the number of pirates in the list.
 */
size_t list_length(pirate_list *pirates);

/**
 * Free all memory associated with the list, including the pirates in the list.
 */
void list_destroy(pirate_list *pirates);

/**
 * Check if the actual number of pirates in the array is "too large"; if it is,
 *  increase the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * If the array capacity was changed, print to stderr the string "Expand to ",
 *  followed by the new capacity of the list and a newline. Here is a possible
 *  print statement:
 *
 *     fprintf(stderr, "Expand to %zu\n", new_capacity);
 *
 * If the capacity was not changed, do nothing.
 */
void list_expand_if_necessary(pirate_list *pirates);

/**
 * Check if the actual number of pirates in the array is "too small"; if it is,
 *  decrease the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * If the array capacity was changed, print to stderr the string "Contract to "
 *  followed by the new capacity of the list. Here is a possible print
 *  statement:
 *
 *     fprintf(stderr, Contract to %zu\n, new_capacity);
 *
 * If the capacity was not changed, do nothing.
 *
 * The capacity of the array must never fall below INITIAL_CAPACITY!
 */
void list_contract_if_necessary(pirate_list *pirates);

/**
 * Append all pirates
*/
void append(pirate_list *pirates, pirate *p);
#endif
