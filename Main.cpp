#include "ANSI_colors.h"
#include "Config.h"
#include "Debug.h"
#include "Stack.h"

int main()
{
    printf(print_lblue("# Implementation of stack.\n"
                       "# (c) BAIDIUSENOV TIMUR, 2023\n\n"));

    Stack stack = {};
	stack_ctor(&stack);
    
    if (stack_push(&stack, {9, 1})) return 0;
    if (stack_push(&stack, {8, 2})) return 0;
    if (stack_push(&stack, {7, 3})) return 0;
    if (stack_push(&stack, {6, 4})) return 0;
    if (stack_push(&stack, {5, 5})) return 0;
    if (stack_push(&stack, {4, 6})) return 0;
    if (stack_push(&stack, {3, 7})) return 0;
    if (stack_push(&stack, {2, 8})) return 0;
    if (stack_push(&stack, {1, 9})) return 0;

    type_el value = {};
    if (stack_pop(&stack, &value)) return 0;
    printf(print_lcyan(type_el_print "\n"), el_print(value));
    if (stack_pop(&stack, &value)) return 0;
    printf(print_lcyan(type_el_print "\n"), el_print(value));
    if (stack_pop(&stack, &value)) return 0;
    printf(print_lcyan(type_el_print "\n"), el_print(value));
    if (stack_pop(&stack, &value)) return 0;
    printf(print_lcyan(type_el_print "\n"), el_print(value));
    if (stack_pop(&stack, &value)) return 0;
    printf(print_lcyan(type_el_print "\n"), el_print(value));
    if (stack_pop(&stack, &value)) return 0;
    printf(print_lcyan(type_el_print "\n"), el_print(value));

	stack_dtor(&stack);

    printf(print_lblue("\nBye\n"));

    return 0;
}
