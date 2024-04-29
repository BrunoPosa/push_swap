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

void	printstack_top_bottom(t_stack *stack)
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

static int	core_logic(t_stack *a, t_stack *b)
{
	if (is_sorted(a) == SUCCESS)
		return (SUCCESS);
	if (a->top > 10)
		a->buckets = split_into_sqrt(a->top) / 2;
	while (a->top > 3)
	{
		if (stack_breaker(a, b) == ERROR)
			return (ERROR);
	}
	if (a->top == 3 && is_sorted(a) != SUCCESS)
	{
		if (sort_three(a, b) == ERROR)
			return (ERROR);
	}
	if (a->top < 3 && is_sorted(a) != SUCCESS)
	{
		if (swap_one(a, 'y') == ERROR)
			return (ERROR);
	}
	if (b->top != 0)
	{
		if (insert_by_max(a, b) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_stack	a;
	t_stack	b;

	if (argc < 2 || (argc == 2 && argv[1][0] == '\0'))
		return (ERROR);
	// I need to handle argument case: 3 2 1a  
	// int i = 1;
	// while (argv[i] != NULL)
	// {
	// 	if (is_just_spacenumbers(argv[i++]) != SUCCESS)
	// 		return (write(2, "Error\n", 6 * sizeof(char)));
	// }
	if (argc == 2 && is_just_spacenumbers(argv[1]) != SUCCESS) 
		return (write(2, "Error\n", 6 * sizeof(char)));
	if (argc == 2 && count_disconnected_spaces(argv[1]) > 0) // count spaces in argv[1], enter if > 1 #Sunday
	{
		if (initializer(input_validator(ft_split(argv[1], ' ')), ft_split(argv[1], ' '), &a, &b) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (initializer(input_validator(argv + 1), argv + 1, &a, &b) != SUCCESS)
			return (ERROR);
	}
	if (core_logic(&a, &b) == ERROR)
		return (write(2, "Error\n", 6 * sizeof(char)));
	// printstack_top_bottom(&a);
	// printstack_top_bottom(&b);
	free(a.array);
	free(b.array);
	return (SUCCESS);
}
