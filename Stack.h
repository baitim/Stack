#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Debug.h"

typedef int type_el;

struct STACK {
    type_el *data;
    int size;
    int capacity;
};

int stack_ctor(STACK *stack, int new_capacity);

int stack_dtor(STACK *stack);

void stack_push(STACK *stack);

int stack_pop(STACK *stack);

#endif // STACK_H
