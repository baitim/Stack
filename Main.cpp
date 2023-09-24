#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int type_el;

#define type_el_print "%d"

#include "ANSI_colors.h"
#include "Debug.h"
#include "Stack.h"

int main ()
{
        printf(print_lblue("# Implementation of stack.\n"
                               "# (c) BAIDIUSENOV TIMUR, 2023\n\n"));

        Stack stack = {nullptr, 0, 0};

		stack_ctor(&stack);

		stack_push(&stack, 5);
        stack_push(&stack, 6);
        stack_push(&stack, 6);
        stack_push(&stack, -1);
        stack_push(&stack, 6);
        stack_push(&stack, 7);

		printf(type_el_print "\n", stack_pop(&stack));
        printf(type_el_print "\n", stack_pop(&stack));
        printf(type_el_print "\n", stack_pop(&stack));

		stack_dtor(&stack);

        printf(print_lblue("Bye\n"));

        return 0;
}
