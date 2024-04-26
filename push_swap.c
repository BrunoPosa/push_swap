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
	struct s_stack stack_b; //make pointers and set to NULL ?

	// input validator here

	// initializer
	if(initializer(argc, argv, &stack_a, &stack_b) == ERROR)
		return (ERROR);

	// Push_Swap logic minefield
	if (is_sorted(&stack_a) == SUCCESS)
		return (free(stack_a.array), free(stack_b.array), SUCCESS);
	if (stack_a.top < 3 && is_sorted(&stack_a) != SUCCESS)
		swap_one(&stack_a, 'y');
	while (stack_a.top > 5)
	{
		stack_breaker(&stack_a, &stack_b);
	}
	if (stack_a.top <= 5 && stack_a.top >= 3 && is_sorted(&stack_a) != SUCCESS)
		sort_five(&stack_a, &stack_b);
	if (stack_b.top != 0)
		insert_by_max(&stack_a, &stack_b);

	// else
	// 	return (free(stack_a.array), free(stack_b.array), printf("Sorry\n"));



	// printstack_top_bottom(&stack_a);
	// printstack_top_bottom(&stack_b);

	// clean up
	free(stack_a.array);
	free(stack_b.array); //general Q: is returning a call to a void funtion as well as a rvalue e.g. (free(s), -1) allowed per the Norm? 'One instruction per line'
	return (SUCCESS);
}
