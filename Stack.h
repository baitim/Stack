#ifndef STACK_H
#define STACK_H

typedef int type_el;

#define type_el_print "%d"

struct Stack {
    type_el *data;
    int size;
    int capacity;
};

#include "Debug.h"

const int DEFAULT_SIZE = 0;

const int DEFAULT_CAPACITY = 5;

const int INT_POISON = -1;

const double MULTIPLIER_CAPACITY = 2;

void stack_ctor(Stack *stack);

void stack_dtor(Stack *stack);

void stack_push(Stack *stack, int value);

type_el stack_pop(Stack *stack);

#endif // STACK_H
