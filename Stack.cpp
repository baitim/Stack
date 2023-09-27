#include "Stack.h"

#include <memory.h>
#include <stdlib.h>

const int DEFAULT_SIZE = 0;

const int DEFAULT_CAPACITY = 5;

const double MULTIPLIER_CAPACITY = 2;

static void stack_increase(Stack *stack);

static void stack_reduce(Stack *stack);

static void *recalloc(void *data, int size);

static void *super_realloc(void *data, int size);

void stack_ctor(Stack *stack)
{
    stack->left_canary_struct = DEFAULT_CANARY;
    stack->right_canary_struct = DEFAULT_CANARY;
    stack->size = DEFAULT_SIZE;
    stack->capacity = DEFAULT_CAPACITY;
    stack->data = (type_el *)recalloc(stack->data, stack->capacity * sizeof(type_el) + sizeof(long long) * 2);
    check_alloc(stack->data);
    *((long long *)stack->data) = DEFAULT_CANARY;
    *((long long *)stack->data + get_right_canary_ptr(stack)) = DEFAULT_CANARY;
    stack->hash = get_data_hash(stack);
    stack_dump(stack);
}

void stack_dtor(Stack *stack)
{
    stack_dump(stack);

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
    stack_dump(stack);

    *((long long *)stack->data + get_right_canary_ptr(stack)) = INT_POISON;
    stack->capacity = (int)(stack->capacity * MULTIPLIER_CAPACITY);
    stack->data = (type_el *)super_realloc(stack->data, stack->capacity * sizeof(type_el) + sizeof(long long) * 2);
    check_alloc(stack->data);
    *((long long *)stack->data + get_right_canary_ptr(stack)) = DEFAULT_CANARY;
    write_hash(stack);
    stack_dump(stack);
}

void stack_reduce(Stack *stack)
{
    stack_dump(stack);

    *((long long *)stack->data + get_right_canary_ptr(stack)) = INT_POISON;
    stack->capacity = (int)(stack->capacity / MULTIPLIER_CAPACITY);
    stack->data = (type_el *)super_realloc(stack->data, stack->capacity * sizeof(type_el) + sizeof(long long) * 2);
    check_alloc(stack->data);
    *((long long *)stack->data + get_right_canary_ptr(stack)) = DEFAULT_CANARY;
    write_hash(stack);
    stack_dump(stack);
}

void stack_push(Stack *stack, type_el value)
{
    stack_dump(stack);

    if (stack->size == stack->capacity)
        stack_increase(stack);

    stack->data[sizeof(long long) / sizeof(type_el) + stack->size++] = value;

    write_hash(stack);
}

type_el stack_pop(Stack *stack)
{
    stack_dump(stack);

    if (stack->size < stack->capacity / (MULTIPLIER_CAPACITY + 1))
        stack_reduce(stack);

    stack->data[sizeof(long long) / sizeof(type_el) + stack->size--] = INT_POISON;
    write_hash(stack);
    return stack->data[sizeof(long long) / sizeof(type_el) + stack->size];
}

int get_right_canary_ptr(const Stack *stack)
{
    return stack->capacity * (int)sizeof(type_el) + (int)sizeof(long long);
}

void *recalloc(void *data, int size)
{
    return memset(super_realloc(data, size), '\0', size);
}

void *super_realloc(void *data, int size)
{
    void *old_data = data;
    void *new_data = realloc(old_data, size);
    if (check_alloc(new_data)) {
        free(data);
        return nullptr;
    }
    return new_data;
}