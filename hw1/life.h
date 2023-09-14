#ifndef __LIFE_H__
#define __LIFE_H__
#include <stdbool.h>
#include <stdio.h>

bool isAlive(int field[], size_t i, size_t size);
bool shouldDie(int field[], size_t i, size_t size);
int* alter(int field[], int new[], size_t size);

#endif
