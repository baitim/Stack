#include "Debug.h"

#include <stdio.h>

#include "ANSI_colors.h"

enum Errors {
    ERROR_NO = 0,
    ERROR_STACK_EMPTY = 1,
    ERROR_STACK_DATA_EMPTY = 2,
    ERROR_STACK_CAPACITY = 4,
    ERROR_STACK_SIZE = 8,
    ERROR_STACK_CAPACITY_LESS_SIZE = 16
};

struct ProcessErrors {
    int error;
    const char *description;
};

const ProcessErrors errors[] = {
    {ERROR_NO, "no errors"},
    {ERROR_STACK_EMPTY, "pointer stack is empty"},
    {ERROR_STACK_DATA_EMPTY, "pointer stack->data is empty"},
    {ERROR_STACK_CAPACITY, "stack->capacity < 0"},
    {ERROR_STACK_SIZE, "stack->size < 0"},
    {ERROR_STACK_CAPACITY_LESS_SIZE, "stack->capacity < stack->size"}
};
const int COUNT_ERRORS = sizeof(errors) / sizeof(ProcessErrors);

static int stack_check_error(Stack *stack);

static void print_error(int error, const char *s);

int stack_dump(Stack *stack, const char *file, const char *func, int line, const char *stk)
{
    int type_error = stack_check_error(stack);

    if (type_error == ERROR_NO)
        return ERROR_NO;

    fprintf(stderr, print_lred("ERROR: in stack[%p], called from FILE = %s, FUNCTION = %s, LINE = %d, with %s\n"), 
                               stack, file, func, line, stk);

    for (int i = 0; i < COUNT_ERRORS; i++) {
        if (errors[i].error == type_error)
            print_error(type_error, errors[i].description);
    }
    return type_error;
}

int stack_check_error(Stack *stack)
{
    int error = ERROR_NO;
    if (!stack)                         error |= ERROR_STACK_EMPTY;
    if (!stack->data)                   error |= ERROR_STACK_DATA_EMPTY;
    if (stack->capacity < 0)            error |= ERROR_STACK_CAPACITY;
    if (stack->size < 0)                error |= ERROR_STACK_SIZE;
    if (stack->capacity < stack->size)  error |= ERROR_STACK_CAPACITY_LESS_SIZE;
    return error; 
}

void print_error(int error, const char *s)
{
    fprintf(stderr, print_lred("ERROR: %d: %s\n"), error, s);
}

void check_alloc(void *pointer, const char *file, const char *func, int line, const char *ptr)
{
    if (pointer) return;
    fprintf(stderr, print_lred("ERROR: in pointer = %p, called from FILE = %s, FUNCTION = %s, LINE = %d, with %s\n"), 
                               pointer, file, func, line, ptr);
}