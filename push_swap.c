/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:52:47 by bposa             #+#    #+#             */
/*   Updated: 2024/04/27 18:52:47 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h> //?
#include <stdarg.h> //?
#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#include "push_swap.h"

// void	printstack_top_bottom(struct s_stack *stack)
// {
// 	int test_i = 1;

// 	printf("printout STACK %c: top=%d\n", stack->name, stack->top);
// 	while (stack->top - test_i > -1)
// 	{
// 		printf("elem:%d at stack  position:%d\n", stack->array[stack->top - test_i], stack->top - test_i);
// 		test_i++;
// 	}
// 	printf("=Top: %d, size: %d\n___________________\n", stack->top, stack->maxsize);
// }

int main(int argc, char *argv[])
{
	struct s_stack stack_a;
	struct s_stack stack_b; //make pointers and set to NULL ?

	// input validator here

	// initializer
	if (initializer(argc, argv, &stack_a, &stack_b) == ERROR)
		return (ERROR);
	if (stack_a.top > 10)
		stack_a.buckets = split_into_sqr(stack_a.top);


	// Push_Swap logic minefield
	if (is_sorted(&stack_a) == SUCCESS)
		return (free(stack_a.array), free(stack_b.array), SUCCESS);
	if (stack_a.top < 3 && is_sorted(&stack_a) != SUCCESS)
		swap_one(&stack_a, 'y');
	while (stack_a.top > 3)
		stack_breaker(&stack_a, &stack_b);
	if (is_sorted(&stack_a) != SUCCESS)
		sort_three(&stack_a, &stack_b);
		// sort_five(&stack_a, &stack_b, find_splitvalue(&stack_a, 2));
	if (stack_b.top != 0)
		insert_by_max(&stack_a, &stack_b);

	// else
	// 	return (free(stack_a.array), free(stack_b.array), printf("Sorry\n"));

	// printstack_top_bottom(&stack_a);
	// printstack_top_bottom(&stack_b);

	// clean up
	free(stack_a.array);
	free(stack_b.array);
	return (SUCCESS);
}
