/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:14:25 by bposa             #+#    #+#             */
/*   Updated: 2024/05/02 17:14:29 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	Sends values back to a in order of max-value.
	Returns SUCCESS, or ERROR on Write fail.
*/
int	insert_by_max(t_stack *a, t_stack *b)
{
	while (b->top > 0)
	{
		while (find_max(b) != b->top - 1)
		{
			if (find_max(b) < b->top / 2)
			{
				if (rotate_one('r', b, 'y') == ERROR)
					return (ERROR);
			}
			else
			{
				if (rotate_one('\0', b, 'y') == ERROR)
					return (ERROR);
			}
		}
		if (pusher(b, a) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
	Sorts stack, that needs to contain exactly 3 values.
	Returns ERROR if not 3 elems, OR on subfunctions' ERRORs. 
	ASCII arythmatic 'a' + 'r' - 'a' replaces a couple 'if's.
*/
int	sort_three(t_stack *stack, t_stack *other_stk)
{
	if (is_sorted(stack) == SUCCESS)
		return (SUCCESS);
	if (find_min(stack) == 2
		|| (stack->name == 'a' && stack->array[1] > stack->array[2]))
	{
		if (rotate_one(stack->name + ('r' - 'a'), stack, 'y') == ERROR)
			return (ERROR);
		return (sort_three(stack, other_stk));
	}
	else if (find_min(stack) == 1
		&& ((stack->name == 'a' && stack->array[2] > stack->array[0])
			|| (stack->name == 'b' && stack->array[2] < stack->array[0])))
	{
		if (rotate_one(stack->name + ('r' - 'b'), stack, 'y') == ERROR)
			return (ERROR);
		return (sort_three(stack, other_stk));
	}
	if (swap_one(stack, 'y') == ERROR)
		return (ERROR);
	return (sort_three(stack, other_stk));
}

/*
	Rotates the stack normally or in reverse until a correct value is on top.
	Returns ERROR on error, otherwise SUCCESS.
*/
int	rotate_cheaply(t_stack *stack, int splitvalue)
{
	int	from_top;
	int	from_bottom;

	from_top = stack->top - 1;
	from_bottom = 0;
	while (stack->array[from_top] >= splitvalue && from_top > 0)
		from_top--;
	from_top = stack->top - 1 - from_top;
	while (stack->array[from_bottom] >= splitvalue
		&& from_bottom < stack->top - 1)
		from_bottom++;
	if (from_top <= from_bottom + 1)
	{
		if (loop_f(from_top, stack, '\0', rotate_one) == ERROR)
			return (ERROR);
	}
	else
	{
		if (loop_f(from_bottom + 1, stack, 'r', rotate_one) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
	Sends to stack b all values less than the split value.
	Returns SUCCESS, or ERROR on errs.
*/
int	stack_breaker(t_stack *a, t_stack *b)
{
	int	splitvalue;

	splitvalue = find_splitvalue(a, a->buckets);
	if (a->buckets > 2)
		a->buckets--;
	while (count_values_under_splitvalue(a, splitvalue) != 0)
	{
		if (a->array[a->top - 1] < splitvalue
			&& a->array[a->top - 1] < a->array[a->top - 2])
		{
			if (pusher(a, b) == ERROR)
				return (ERROR);
		}
		else if (a->array[a->top - 2] < splitvalue)
		{
			if (swap_one(a, 'y') == ERROR)
				return (ERROR);
		}
		else
		{
			if (rotate_cheaply(a, splitvalue) == ERROR)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int	core_logic(t_stack *a, t_stack *b)
{
	if (is_sorted(a) == SUCCESS)
		return (SUCCESS);
	if (a->top > 15)
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
