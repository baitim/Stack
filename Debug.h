#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Stack.h"

long long make_number_canary();

const long long DEFAULT_CANARY = make_number_canary();

int stack_dump(Stack *stack, const char *file, const char *func, int line, const char *stk);

#define STACK_DUMP(stk) stack_dump(stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, #stk) 

void check_alloc(void *pointer, const char *file, const char *func, int line, const char *ptr);

#define CHECK_ALLOC(pointer) check_alloc(pointer, __FILE__, __PRETTY_FUNCTION__, __LINE__, #pointer) 

void print_stack_pointers(const Stack *stack);

int calculate_hash(const Stack *stack);

#endif // DEBUG_H
