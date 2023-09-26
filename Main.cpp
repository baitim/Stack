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

    stack_push(&stack, 1);
    stack_push(&stack, 6);
    stack_push(&stack, 7);
    stack_push(&stack, 2);
    stack_push(&stack, 3);
    stack_push(&stack, 4);
    stack_push(&stack, 5);

	printf(type_el_print "\n", stack_pop(&stack));
    printf(type_el_print "\n", stack_pop(&stack));
    printf(type_el_print "\n", stack_pop(&stack));
    printf(type_el_print "\n", stack_pop(&stack));
    printf(type_el_print "\n", stack_pop(&stack));
    printf(type_el_print "\n", stack_pop(&stack));
    printf(type_el_print "\n", stack_pop(&stack));

	stack_dtor(&stack);

    printf(print_lblue("\nBye\n"));

    return 0;
}
