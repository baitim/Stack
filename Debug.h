#ifndef DEBUG_H
#define DEBUG_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"

int stack_dump(STACK *stack);

//#define STACK_DUMP(stk) stack_dump(stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, #stk) 

int stack_check_error(STACK *stack);

#endif // DEBUG_H
