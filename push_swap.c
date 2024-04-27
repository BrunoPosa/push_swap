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

int	main(int argc, char *argv[])
{
	t_stack	a;
	t_stack	b;

	if (initializer(argc, argv, &a, &b) == ERROR)
		return (ERROR);
	if (is_sorted(&a) == SUCCESS)
	{
		free(a.array);
		free(b.array);
		return (SUCCESS);
	}
	if (a.top > 10)
		a.buckets = split_into_sqrt(a.top);
	while (a.top > 3)
	{
		if (stack_breaker(&a, &b) == ERROR)
			return (write(2, "Error\n", 6 * sizeof(char)));
	}
	if (a.top == 3 && is_sorted(&a) != SUCCESS)
	{
		if (sort_three(&a, &b) == ERROR)
			return (write(2, "Error\n", 6 * sizeof(char)));
	}
	if (a.top < 3 && is_sorted(&a) != SUCCESS)
	{
		if (swap_one(&a, 'y') == ERROR)
			return (write(2, "Error\n", 6 * sizeof(char)));
	}
	if (b.top != 0)
	{
		if (insert_by_max(&a, &b) == ERROR)
			return (write(2, "Error\n", 6 * sizeof(char)));
	}
	free(a.array);
	free(b.array);
	return (SUCCESS);
}
