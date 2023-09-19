#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ANSI_colors.h"
#include "Debug.h"
#include "Stack.h"

int main ()
{
        printf(ANSI_LIGHT_BLUE "# Implementation of stack.\n"
                               "# (c) BAIDIUSENOV TIMUR, 2023\n\n" ANSI_DEFAULT_COLOR);

        STACK stack = {nullptr, 0, 0};

		stack_ctor(&stack);

		stack_push(&stack, 5);

		printf("%d\n", stack_pop(&stack));

		stack_dtor(&stack);

        printf(ANSI_LIGHT_BLUE "Bye.\n" ANSI_DEFAULT_COLOR);

        return 0;
}
