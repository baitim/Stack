#ifndef STACK_H
#define STACK_H

#include "Config.h"

struct Stack {
    long long left_canary_struct;
    type_el *data;
    int size;
    int capacity;
    int hash;
    long long right_canary_struct;
};

#include "Debug.h"

void stack_ctor(Stack *stack);

void stack_dtor(Stack *stack);

void stack_push(Stack *stack, type_el value);

type_el stack_pop(Stack *stack);

int get_right_canary_ptr(const Stack *stack);

#endif // STACK_H
