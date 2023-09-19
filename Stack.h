#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int type_el;

struct STACK {
    type_el *data;
    int size;
    int capacity;
};

#include "Debug.h"

const double MULTIPLIER_CAPACITY = 2;

void stack_ctor(STACK *stack);

void stack_dtor(STACK *stack);

void stack_increase(STACK *stack);

void stack_reduce(STACK *stack);

void stack_push(STACK *stack, int value);

int stack_pop(STACK *stack);

#endif // STACK_H
