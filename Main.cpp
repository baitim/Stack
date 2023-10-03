#include "ANSI_colors.h"
#include "Config.h"
#include "Debug.h"
#include "Stack.h"

int main()
{
    printf(print_lblue("# Implementation of stack.\n"
                       "# (c) BAIDIUSENOV TIMUR, 2023\n\n"));
    
    Stack stack = {};
	if (stack_ctor(&stack)) return 0;

    for (int i = 0; i < 100000; i++)
        if (stack_push(&stack, i)) return 0;

    type_el value = {};
    for (int i = 0; i < 100000; i++)
        if (stack_pop(&stack, &value)) return 0;

    stack_dtor(&stack);

    printf(print_lblue("\nBye\n"));

    return 0;
}
