#ifndef DEBUG_H
#define DEBUG_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ANSI_colors.h"
#include "Stack.h"

enum ERRORS {
    ERROR_NO = 0,
    ERROR_STACK_EMPTY = 1,
    ERROR_STACK_DATA_EMPTY = 2,
    ERROR_STACK_CAPACITY = 4,
    ERROR_STACK_SIZE = 8,
    ERROR_STACK_CAPACITY_LESS_SIZE = 16
};

int stack_dump(STACK *stack, const char *file, const char *func, int line, const char *stk);

#define STACK_DUMP(stk) stack_dump(stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, #stk) 

int stack_check_error(STACK *stack);

#endif // DEBUG_H
