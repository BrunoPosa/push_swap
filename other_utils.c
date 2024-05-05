/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:14:50 by bposa             #+#    #+#             */
/*   Updated: 2024/05/05 14:20:56 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_to_top_or_bottom(t_stack *a, t_stack *b, int midbucket)
{
	if (pusher(a, b) == ERROR)
		return (ERROR);
	if (b->top > 1 && b->array[b->top - 1] < midbucket)
	{
		if (rotate_one('\0', b, 'y') == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	count_values_under_splitvalue(t_stack *stack, int splitvalue)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i != stack->top)
	{
		if (stack->array[i] < splitvalue)
			count++;
		i++;
	}
	if (count == 0)
	{
		if (stack->buckets > 2)
			stack->buckets--;
	}
	return (count);
}

int	loop_f(int n, t_stack *stack, char r, int (*f)(char, t_stack *, char))
{
	while (n != 0)
	{
		if (f(r, stack, 'y') == ERROR)
			return (ERROR);
		n--;
	}
	return (SUCCESS);
}

/*
	find_max returns (int) index of the maximum value in the given stack.
*/
int	find_max(t_stack *stack)
{
	int		i;
	int		max;

	if (stack->top == 0)
		return (ERROR);
	i = stack->top - 1;
	max = i;
	while (i >= 0)
	{
		if (stack->array[i] > stack->array[max])
			max = i;
		i--;
	}
	return (max);
}

/*
	find_min returns (int) index of the minimum value in the given stack.
*/
int	find_min(t_stack *stack)
{
	int		i;
	int		min;

	i = 0;
	min = 0;
	if (stack->top == 0)
		return (ERROR);
	while (i != stack->top)
	{
		if (stack->array[i] < stack->array[min])
			min = i;
		i++;
	}
	return (min);
}
