#ifndef STACK_H
#define STACK_H

typedef int type_el;

#define type_el_print "%d"

struct Stack {
    long long left_canary;
    type_el *data;
    int size;
    int capacity;
    int hash;
    long long right_canary;
};

#include "Debug.h"

void stack_ctor(Stack *stack);

void stack_dtor(Stack *stack);

void stack_push(Stack *stack, int value);

type_el stack_pop(Stack *stack);

#endif // STACK_H
