#define _POSIX_C_SOURCE 200809L
#define MAX_LINE 127

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skills_list.h"
#include "pirate.h"


struct list_node {
    char skill[MAX_LINE+1];
    node *next;
};

struct skills_list_instance_t{
    node *head;
    node *tail;
};

/*
Allocate memory for linked-list
*/
skills_list *skills_list_create(){
    skills_list *skll = malloc(sizeof(skills_list));
    skll->head = NULL;
    return skll;
}

/*
Compare skills for their sorted order
*/
int skills_list_compare(char *a, char *b){
    return strcmp(a, b);
}

/*
Append skills to linked list in sorted order
*/
void skills_list_append(skills_list *skll, char *skill_to_add){
    struct list_node *add = malloc(sizeof(struct list_node));
    strncpy(add->skill, skill_to_add, MAX_LINE);
    add->skill[MAX_LINE] = '\0';
    add->next = NULL;

    if (skll->head == NULL) {
        // Add automatically to head if list is empty
        skll->head = add;
        skll->tail = add;
        return;
    } else if (skills_list_compare(add->skill, skll->head->skill) < 0){
        // Add to head if skill comes before or is equal to other skills
        add->next = skll->head;
        skll->head = add;
        return;
    } else if (skills_list_compare(add->skill, skll->tail->skill) > 0){
        // Add to tail if skill comes after all other skills
        skll->tail->next = add;
        skll->tail = add;
        return;
    } else {
        // Add to correct position within linked-list
        struct list_node *current = skll->head;
        while (current->next != NULL && skills_list_compare(add->skill, current->next->skill) > 0){
            current = current->next;
        }
        add->next = current->next;
        current->next = add;
        return;
    }
}

/*
Get length of linked list
*/
int skills_list_len(skills_list *skll){
    int len = 0;
    node *end = skll->head;
    while (end != NULL) {
        end = end->next;
        len++;
    } 
    return len;
}

/*
Get a skill based off index
*/
char* skills_list_get(skills_list *skll, int idx){
    if (idx >= skills_list_len(skll)){
        fprintf(stderr, "Index is out of bounds");
        exit(1);
    }
    int len = 0;
    node *end = skll->head;
    while (len != idx){
        end = end->next;
        len++;
    }
    return end->skill;
}

/*
Destroy linked-list
*/
void skills_list_destroy(skills_list *skll){
    node *end = skll->head;
    while (end != NULL) {
        node *destroy = end;
        end = end->next;
        free(destroy);
    } 
    free(skll);
}




