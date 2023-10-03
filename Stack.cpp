#include "Stack.h"

#include <memory.h>
#include <stdlib.h>

const int DEFAULT_SIZE = 0;

const int DEFAULT_CAPACITY = 7;

const double MULTIPLIER_CAPACITY = 2;

enum RESIZE_MULTIPLIER {
    MULTIPLIER_REDUCE   = -1,
    MULTIPLIER_INCREASE =  1
};

static Errors stack_resize(Stack *stack, int multiplier);

Errors stack_ctor(Stack *stack)
{
    stack->left_canary_struct = DEFAULT_CANARY;
    stack->right_canary_struct = DEFAULT_CANARY;
    stack->size = DEFAULT_SIZE;
    stack->capacity = DEFAULT_CAPACITY;
    type_el *new_data = (type_el *)realloc(stack->data, DEFAULT_CAPACITY * sizeof(type_el) + sizeof(long long) * 2);
    if (!new_data)
        return ERROR_REALLOC_FAIL;
    memset(new_data, POISON_BYTE, DEFAULT_CAPACITY);
    if (!new_data)
        return ERROR_REALLOC_FAIL;
    else if(stack->data != new_data)
        stack->data = new_data;

    *((long long *)stack->data) = DEFAULT_CANARY;
    stack->data = (type_el *)((long long *)stack->data + 1);
    *((long long *)stack->data + get_right_canary_index(stack)) = DEFAULT_CANARY;
    stack->hash = get_hash(stack);
    return stack_dump(stack); 
}

Errors stack_dtor(Stack *stack)
{
    Errors error = stack_dump(stack);
    if (error) return error;

    stack->data = (type_el *)((char *)stack->data - sizeof(long long));
    free(stack->data);
    stack->data = nullptr;
    stack->size = POISON_BYTE;
    stack->capacity = POISON_BYTE;
    stack->left_canary_struct = POISON_BYTE;
    stack->right_canary_struct = POISON_BYTE;
    stack->hash = POISON_BYTE;
    return error;
}

static Errors stack_resize(Stack *stack, int multiplier)
{
    Errors error = stack_dump(stack);
    if (error) return error;
    if (multiplier == MULTIPLIER_REDUCE)    stack->capacity = (int)(stack->capacity / MULTIPLIER_CAPACITY);
    if (multiplier == MULTIPLIER_INCREASE)  stack->capacity = (int)(stack->capacity * MULTIPLIER_CAPACITY);
    stack->data = (type_el *)((long long *)stack->data - 1);
    *((long long *)stack->data) = POISON_BYTE;
    *((long long *)stack->data + 1 + get_right_canary_index(stack)) = POISON_BYTE;
    type_el *new_data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el) + sizeof(long long) * 2);
    printf("cap = %d\tnew_data = %p\n", stack->capacity, new_data);
    if (!new_data)
        return ERROR_REALLOC_FAIL;
    else if(stack->data != new_data)
        stack->data = new_data; 

    *((long long *)stack->data) = DEFAULT_CANARY;
    stack->data = (type_el *)((long long *)stack->data + 1);
    *((long long *)stack->data + get_right_canary_index(stack)) = DEFAULT_CANARY;
    stack->hash = get_hash(stack);
    return stack_dump(stack);
}

Errors stack_push(Stack *stack, type_el value)
{
    Errors error = stack_dump(stack);
    if (error) return error;

    if (stack->size == stack->capacity)
        error = stack_resize(stack, MULTIPLIER_INCREASE);

    if (error) return error;

    stack->data[stack->size++] = value;
    stack->hash = get_hash(stack);
    return stack_dump(stack);
}

Errors stack_pop(Stack *stack, type_el *value)
{
    Errors error = stack_dump(stack);
    if (error) return error;

    if (stack->size < stack->capacity / (MULTIPLIER_CAPACITY + 1))
        error = stack_resize(stack, MULTIPLIER_REDUCE);

    if (error) return error;

    stack->data[--stack->size] = POISON_EL;
    stack->hash = get_hash(stack);
    *value = stack->data[stack->size];
    return stack_dump(stack);
}

int get_left_canary_index(const Stack */*stack*/)
{
    return -1;
}

int get_right_canary_index(const Stack *stack)
{
    return ((int)sizeof(type_el) * stack->capacity + ((int)sizeof(type_el) * stack->capacity) % 8) / (int)sizeof(long long);
}
