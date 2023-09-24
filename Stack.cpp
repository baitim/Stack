#include "Stack.h"

#include <stdlib.h>

static void stack_increase(Stack *stack);

static void stack_reduce(Stack *stack);

void stack_ctor(Stack *stack)
{
    stack->size = DEFAULT_SIZE;
    stack->capacity = DEFAULT_CAPACITY;
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el));
    CHECK_ALLOC(stack->data);

    STACK_DUMP(stack);
}

void stack_dtor(Stack *stack)
{
    STACK_DUMP(stack);

    free(stack->data);
    stack->data = nullptr;
    stack->size = INT_POISON;
    stack->capacity = INT_POISON;
}

void stack_increase(Stack *stack)
{
    STACK_DUMP(stack);

    stack->capacity = (int)(stack->capacity * MULTIPLIER_CAPACITY);
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el));
    CHECK_ALLOC(stack->data);

    STACK_DUMP(stack);
}

void stack_reduce(Stack *stack)
{
    STACK_DUMP(stack);

    stack->capacity = (int)(stack->capacity / MULTIPLIER_CAPACITY);
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el));
    CHECK_ALLOC(stack->data);

    STACK_DUMP(stack);
}

void stack_push(Stack *stack, int value)
{
    STACK_DUMP(stack);

    if (stack->size == stack->capacity)
        stack_increase(stack);

    stack->data[stack->size++] = value;
}

type_el stack_pop(Stack *stack)
{
    STACK_DUMP(stack);

    if (stack->size < stack->capacity / (MULTIPLIER_CAPACITY + 1))
        stack_reduce(stack);

    stack->data[stack->size--] = INT_POISON;
    return stack->data[stack->size];
}
