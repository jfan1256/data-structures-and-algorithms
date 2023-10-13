#ifndef __SKILLS_LIST_H__
#define __SKILLS_LIST_H__

/*
Header file for skills list for Hookbook assignments for CPSC 223 Fall 2023.

Author: [Jonathan Fan]
Modified by: [Jonathan Fan] on [10/13/2023]
Changelog: [Added: All the required functionalities for skills_list]
*/

/**
 * Type of a list of skills, as an opaque struct.
 */
typedef struct skills_list_instance_t skills_list;

/*
Set up linked-list node framework
*/
typedef struct list_node node;

/*
Allocate memory for linked-list
*/
skills_list *skills_list_create();

/*
Compare skills for their sorted order
*/
int skills_list_compare(char *a, char *b);

/*
Append skills to linked list in sorted order
*/
void skills_list_append(skills_list *skll, char *skill_to_add);

/*
Get length of linked-list
*/
int skills_list_len(skills_list *skll);

/*
Get a skill based off index
*/
char* skills_list_get(skills_list *skll, int idx);

/*
Destroy linked-list
*/
void skills_list_destroy(skills_list *skll);

#endif