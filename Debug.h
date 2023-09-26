#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int INT_POISON = -1;

#include "Stack.h"

long long make_number_canary();

const long long DEFAULT_CANARY = make_number_canary();

#define stack_dump(stk) stack_dump_(stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, #stk) 

int stack_dump_(Stack *stack, const char *file, const char *func, int line, const char *stk);

#define check_alloc(pointer) check_alloc_(pointer, __FILE__, __PRETTY_FUNCTION__, __LINE__, #pointer) 

int check_alloc_(void *pointer, const char *file, const char *func, int line, const char *ptr);

void print_stack_pointers(const Stack *stack);

int get_data_hash(Stack *stack);

void write_hash(Stack *stack);

#endif // DEBUG_H
