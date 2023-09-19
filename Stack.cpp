#include "Stack.h"

void stack_ctor(STACK *stack)
{
    STACK_DUMP(stack);

    stack->size = 0;
    stack->capacity = 5;
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el));

    STACK_DUMP(stack);
}

void stack_dtor(STACK *stack)
{
    STACK_DUMP(stack);

    free(stack->data);
    stack->data = nullptr;
    stack->size = -1;
    stack->capacity = -1;
}

void stack_increase(STACK *stack)
{
    STACK_DUMP(stack);

    stack->capacity = (int)(stack->capacity * MULTIPLIER_CAPACITY);
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el));

    STACK_DUMP(stack);
}

void stack_reduce(STACK *stack)
{
    STACK_DUMP(stack);

    stack->capacity = (int)(stack->capacity / MULTIPLIER_CAPACITY);
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el));

    STACK_DUMP(stack);
}

void stack_push(STACK *stack, int value)
{
    STACK_DUMP(stack);

    if (stack->size == stack->capacity)
        stack_increase(stack);

    stack->data[stack->size++] = value;
}

int stack_pop(STACK *stack)
{
    STACK_DUMP(stack);

    if (stack->size < stack->capacity / (MULTIPLIER_CAPACITY + 1))
        stack_increase(stack);

    stack->data[stack->size--] = -1;
    return stack->data[stack->size];
}
