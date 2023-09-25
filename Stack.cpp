#include "Stack.h"

#include <stdlib.h>

const int DEFAULT_SIZE = 0;

const int DEFAULT_CAPACITY = 5;

const double MULTIPLIER_CAPACITY = 2;

static void stack_increase(Stack *stack);

static void stack_reduce(Stack *stack);

void stack_ctor(Stack *stack)
{
    stack->left_canary_struct = DEFAULT_CANARY;
    stack->right_canary_struct = DEFAULT_CANARY;
    stack->hash = calculate_hash(stack);
    stack->size = DEFAULT_SIZE;
    stack->capacity = DEFAULT_CAPACITY;
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el) + sizeof(long long) * 2);
    CHECK_ALLOC(stack->data);
    *((long long *)stack->data) = DEFAULT_CANARY;
    *((long long *)stack->data + stack->capacity * sizeof(type_el) + sizeof(long long)) = DEFAULT_CANARY;
    STACK_DUMP(stack);
}

void stack_dtor(Stack *stack)
{
    STACK_DUMP(stack);

    free(stack->data);
    stack->data = nullptr;
    stack->size = INT_POISON;
    stack->capacity = INT_POISON;
    stack->left_canary_struct = INT_POISON;
    stack->right_canary_struct = INT_POISON;
    stack->hash = INT_POISON;
}

void stack_increase(Stack *stack)
{
    STACK_DUMP(stack);

    *((long long *)stack->data + stack->capacity * sizeof(type_el) + sizeof(long long)) = INT_POISON;
    stack->capacity = (int)(stack->capacity * MULTIPLIER_CAPACITY);
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el) + sizeof(long long) * 2);
    CHECK_ALLOC(stack->data);
    *((long long *)stack->data + stack->capacity * sizeof(type_el) + sizeof(long long)) = DEFAULT_CANARY;
    write_hash(stack);
    STACK_DUMP(stack);
}

void stack_reduce(Stack *stack)
{
    STACK_DUMP(stack);

    *((long long *)stack->data + stack->capacity * sizeof(type_el) + sizeof(long long)) = INT_POISON;
    stack->capacity = (int)(stack->capacity / MULTIPLIER_CAPACITY);
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el) + sizeof(long long) * 2);
    CHECK_ALLOC(stack->data);
    *((long long *)stack->data + stack->capacity * sizeof(type_el) + sizeof(long long)) = DEFAULT_CANARY;
    write_hash(stack);
    STACK_DUMP(stack);
}

void stack_push(Stack *stack, int value)
{
    STACK_DUMP(stack);

    if (stack->size == stack->capacity)
        stack_increase(stack);

    stack->data[sizeof(long long) / sizeof(type_el) + stack->size++] = value;

    write_hash(stack);
}

type_el stack_pop(Stack *stack)
{
    STACK_DUMP(stack);

    if (stack->size < stack->capacity / (MULTIPLIER_CAPACITY + 1))
        stack_reduce(stack);

    stack->data[sizeof(long long) / sizeof(type_el) + stack->size--] = INT_POISON;
    write_hash(stack);
    return stack->data[sizeof(long long) / sizeof(type_el) + stack->size];
}
