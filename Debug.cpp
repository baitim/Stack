#include "Debug.h"

int stack_dump(STACK *stack, const char *file, const char *func, int line, const char *stk)
{
    int error = stack_check_error(stack);
    return error;
}

int stack_check_error(STACK *stack)
{
    int error = 0;
    if (!stack)
        error |= 1;
    if (!stack->data)
        error |= 2;
    if (!stack->capacity)
        error |= 4;
    if (!stack->size)
        error |= 8;
    if (stack->capacity < stack->size)
        error |= 16;
    return error; 
}