#include "Stack.h"

int stack_ctor(STACK *stack, int new_capacity)
{
    stack_dump(stack);

    stack->capacity = new_capacity;
    stack->data = (type_el *)realloc(stack->data, stack->capacity * sizeof(type_el));

    stack_dump(stack);
}

int stack_dtor(STACK *stack)
{
    stack_dump(stack);

    stack->data = nullptr;
    stack->size = -1;
    stack->capacity = -1;
}

void stack_push(STACK *stack)
{
    stack_dump(stack);

    stack->data = nullptr;
    stack->size = -1;
    stack->capacity = -1;
}

int stack_pop(STACK *stack)
{
    stack_dump(stack);

    stack->data = nullptr;
    stack->size = -1;
    stack->capacity = -1;
}
