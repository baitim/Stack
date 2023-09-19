#include "Debug.h"

int stack_dump(STACK *stack, const char *file, const char *func, int line, const char *stk)
{
    int error = stack_check_error(stack);
    if (error == ERROR_NO)
        return ERROR_NO;
    fprintf(stderr, ANSI_LIGHT_RED "ERROR: in stack[%p], called from FILE = %s, FUNCTION = %s, LINE = %d, with %s\n" 
                    ANSI_DEFAULT_COLOR, stack, file, func, line, stk);
    if (error == ERROR_STACK_EMPTY)
        fprintf(stderr, ANSI_LIGHT_RED "ERROR: %d: pointer stack is empty\n" ANSI_DEFAULT_COLOR, error);
    if (error == ERROR_STACK_DATA_EMPTY)
        fprintf(stderr, ANSI_LIGHT_RED "ERROR: %d: pointer stack->data  is empty\n" ANSI_DEFAULT_COLOR, error);
    if (error == ERROR_STACK_CAPACITY)
        fprintf(stderr, ANSI_LIGHT_RED "ERROR: %d: stack->capacity < 0>\n" ANSI_DEFAULT_COLOR, error);
    if (error == ERROR_STACK_SIZE)
        fprintf(stderr, ANSI_LIGHT_RED "ERROR: %d: stack->size < 0\n" ANSI_DEFAULT_COLOR, error);
    if (error == ERROR_STACK_CAPACITY_LESS_SIZE)
        fprintf(stderr, ANSI_LIGHT_RED "ERROR: %d: stack->capacity < stack->size\n" ANSI_DEFAULT_COLOR, error);
    return error;
}

int stack_check_error(STACK *stack)
{
    int error = ERROR_NO;
    if (!stack) error |= ERROR_STACK_EMPTY;
    if (!stack->data) error |= ERROR_STACK_DATA_EMPTY;
    if (stack->capacity < 0) error |= ERROR_STACK_CAPACITY;
    if (stack->size < 0) error |= ERROR_STACK_SIZE;
    if (stack->capacity < stack->size)  error |= ERROR_STACK_CAPACITY_LESS_SIZE;
    return error; 
}