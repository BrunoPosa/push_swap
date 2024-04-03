#include <stdlib.h>
#include <unistd.h> //?
#include <stdarg.h> //?
#include <stdio.h>
#include <limits.h>
#include "push_swap.h"
#include <stdio.h>

void	printstack_top_bottom(struct s_stack *stack)
{
	int test_i = 1;

	printf("printout STACK %c: top=%d\n", stack->name, stack->top);
	while (stack->top - test_i > -1)
	{
		printf("elem:%d at stack  position:%d\n", stack->array[stack->top - test_i], stack->top - test_i);
		test_i++;
	}
	printf("=Top: %d, size: %d\n___________________\n", stack->top, stack->maxsize);
}

/*
	=========================
	|		  MAIN  		|
	=========================
*/
// returns non-zero on error
int main(int argc, char *argv[])
{ 
	struct s_stack stack_a;
	struct s_stack stack_b;

	if(initializer(argc, argv, &stack_a, &stack_b) == ERROR)
		return (ERROR);

	// Push_Swap algo logic here


	printstack_top_bottom(&stack_a);
	printstack_top_bottom(&stack_b);


	// clean up
	free(stack_a.array);
	free(stack_b.array);
	return (SUCCESS);
}