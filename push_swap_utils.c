/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:52:25 by bposa             #+#    #+#             */
/*   Updated: 2024/05/02 17:05:51 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	find_splitvalue returns the next bigger value after values in current bucket.
	Current bucket contains <= bucket-size amount of smallest numbers in stack.
	(bucket-size = total elements / number of buckets).
*/
int	find_splitvalue(t_stack *stack, int buckets)
{
	long	i;
	long	j;
	int		smaller_values;

	i = 0;
	j = 0;
	smaller_values = 0;
	while (i != stack->top && buckets > 1)
	{
		j = 0;
		smaller_values = 0;
		while (j != stack->top)
		{
			if (stack->array[i] > stack->array[j])
				smaller_values++;
			j++;
		}
		if (smaller_values == stack->top / buckets)
			return (stack->array[i]);
		i++;
	}
	return (ERROR);
}

/* 
	If sorted, returns SUCCESS, if not, returns ERROR
*/
int	is_sorted(t_stack *stack)
{
	int	i;

	i = stack->top - 1;
	if (stack->top == 0 || stack->top == 1)
		return (SUCCESS);
	while (i >= 1)
	{
		if (stack->name == 'a' && stack->array[i] > stack->array[i - 1])
			return (ERROR);
		if (stack->name == 'b' && stack->array[i] < stack->array[i - 1])
			return (ERROR);
		i--;
	}
	return (SUCCESS);
}

/*
	swap_one - does the swapping of top two values (sa or sb).
	If do_i_print flag is 'y', prints out the operation it did.
	Returns SUCCESS or positive number, ERROR if nothing to swap or write fails.
*/
int	swap_one(t_stack *stack, char do_i_print)
{
	int	temp;

	if (stack->top == 0 || stack->top == 1)
		return (ERROR);
	temp = stack->array[stack->top - 1];
	stack->array[stack->top - 1] = stack->array[stack->top - 2];
	stack->array[stack->top - 2] = temp;
	if (do_i_print == 'y')
		return (ft_printf("s%c\n", stack->name));
	return (SUCCESS);
}

/*
	pusher - performs pa or pb, printing out 'pa' or 'pb'.
	Returns -1 if did't execute the push and on error.
*/
int	pusher(t_stack *from_stack, t_stack *into_stack)
{
	if (from_stack->top == 0)
		return (-1);
	into_stack->array[into_stack->top] = from_stack->array[from_stack->top - 1];
	into_stack->top++;
	from_stack->top--;
	from_stack->array[from_stack->top] = 0;
	if (ft_printf("p%c\n", into_stack->name) == -1)
		return (-1);
	return (0);
}

/*
	rotate_one - does the actual rotating, reverse or normal,
	depending on char r_for_reverse flag being 'r' or not.
	Prints if do_i_print flag is 'y'.
	Returns 0 or positive num on success, and -1 on error.
*/
int	rotate_one(char r_for_reverse, t_stack *stack, char do_i_print)
{
	int	temp;

	temp = 0;
	if (stack->top == 0 || stack->top == 1)
		return (ERROR);
	if (r_for_reverse == 'r')
	{
		temp = stack->array[0];
		ft_memmove(&stack->array[0], &stack->array[1], stack->top);
		stack->array[stack->top - 1] = temp;
	}
	else
	{
		temp = stack->array[stack->top - 1];
		ft_memmove(&stack->array[1], &stack->array[0], stack->top);
		stack->array[0] = temp;
	}
	if (do_i_print == 'y')
	{
		if (r_for_reverse == 'r')
			return (ft_printf("rr%c\n", stack->name));
		return (ft_printf("r%c\n", stack->name));
	}
	return (SUCCESS);
}
