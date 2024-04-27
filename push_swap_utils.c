/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:52:25 by bposa             #+#    #+#             */
/*   Updated: 2024/04/27 20:39:49 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	For now, initializer sets but also prints out what it sets. Later I plan for it to call InputValidator function.
*/
int	initializer(int argc, char **argv, t_stack *stack_a, t_stack *stack_b)
{
	stack_a->name = 'a';
	stack_a->buckets = 2;
	stack_a->array = NULL;
	stack_a->maxsize = argc;
	stack_a->top = argc - 1;
	stack_b->name = 'b';
	stack_b->buckets = 2;
	stack_b->array = NULL;
	stack_b->maxsize = argc;
	stack_b->top = 0;
    int i;

	i = 1;
	// sanity check
	if (argc < 2)
		return (ERROR);
	// allocate stacks space and initialize to \0s, check malloc fails
	stack_a->array = (int *)ft_calloc(stack_a->maxsize, sizeof(int));
	if (!stack_a->array)
		return (-printf("E")); //-1
	stack_b->array = (int *)ft_calloc(stack_b->maxsize, sizeof(int));
	if (!stack_b->array)
		return (-printf("E")); //-1

	// fill stack_a with arguments, converting them to integers
	while (stack_a->top - i >= 0)
	{
		stack_a->array[stack_a->top - i] = ft_atoi(argv[i]);
		// printf("element (%d) goes to stack_a position=%d\n", stack_a->array[stack_a->top - i], stack_a->top - i);
		i++;
	}
    return(SUCCESS);
}

/*
	sends back values in order of max-value to stack a
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
	Sends over to other stack all values less than the split value. Returns SUCCESS if breaks the stack and ERROR on errs. 
*/
int	stack_breaker(t_stack *a, t_stack *b)
{
	int	splitvalue;

	splitvalue = find_splitvalue(a, a->buckets);
	if (a->buckets > 2)
		a->buckets--;
	while (count_values_under_splitvalue(a, splitvalue) != 0)
	{
		if (a->array[a->top - 1] < splitvalue)
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

int	split_into_sqr(int number)
{
	int	result;

	result = 1;
	while ((result * result) <= number)
		result++;
	if (result * result == number)
		return (result);
	else
		return (result - 1);
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
	return (count);
}

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
	Rotates the stack normally or in reverse until a correct value is on top.
	Returns ERROR on error, otherwise SUCCESS.
*/
int rotate_cheaply(t_stack *stack, int splitvalue)
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
	find_max returns (int) index of the maximum value in the given stack.
*/
int find_max(t_stack *stack)
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
int find_min(t_stack *stack)
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

/* 
	If sorted, returns SUCCESS, if not, returns ERROR
*/
int is_sorted(t_stack *stack)
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
	If print flag is 'p', prints out the operation it did.
	Returns SUCCESS or positive number, ERROR if nothing to swap or write fails.
*/
int swap_one(t_stack *stack, char do_i_print)
{
	int	temp;

	if (stack->top == 0 || stack->top == 1)
		return (ERROR);
	temp = stack->array[stack->top - 1];
	stack->array[stack->top - 1] = stack->array[stack->top - 2];
	stack->array[stack->top - 2] = temp;
	if (do_i_print == 'y')
		return (printf("s%c\n", stack->name));
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
	if (printf("p%c\n", into_stack->name) == -1)
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
		my_memmove(&stack->array[0], &stack->array[1], stack->top);
		stack->array[stack->top - 1] = temp;
	}
	else
	{
		temp = stack->array[stack->top - 1];
		my_memmove(&stack->array[1], &stack->array[0], stack->top);
		stack->array[0] = temp;
	}
	if (do_i_print == 'y')
	{
		if (r_for_reverse == 'r')
			return (printf("rr%c\n", stack->name));
		return (printf("r%c\n", stack->name));
	}
	return (SUCCESS);
}
