/*
	=========================
	|	 PUSH_SWAP UTILS	|
	=========================
*/

#include "push_swap.h"


/*
	For now, initializer sets but also prints out what it sets. Later I plan for it to call InputValidator function.
*/

int		initializer(int argc, char **argv, struct s_stack *stack_a, struct s_stack *stack_b)
{
    stack_a->name = 'a';
	// ft_bzero(stack_a->cmd, 3);
	stack_a->array = NULL;
	stack_a->maxsize = argc;
	stack_a->top = argc - 1; //*index of* the NEXT element in array
	stack_b->name = 'b';
	// ft_bzero(stack_b->cmd, 3);
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
		printf("element at i=%d (%d) goes to stack_a position=%ld\n", i, stack_a->array[stack_a->top - i], stack_a->top - i);
		i++;
	}
    return(SUCCESS);
}

int	sort_five(struct s_stack *a, struct s_stack *b)
{
	int	mid;
	
	mid = find_midvalue(a);
	while (a->top > 3 && is_sorted(a) != SUCCESS)
	{
		if (a->array[a->top - 1] < mid)
			pusher(a, b);
		else if (a->array[a->top - 2] < mid)
		{
			swap_one(a, 'y');
			if (is_sorted(a) != SUCCESS)
				pusher(a, b);
		}
		else if (a->array[0] < mid)
		{
			rotate_one('r', a, 'y');
			if (is_sorted(a) != SUCCESS)
				pusher(a, b);
		}
		else
			rotate_one('\0', a, 'y');
	}
	sort_three(a, b);
	while(b->top != 0)
		pusher(b, a);
	if (is_sorted(a) != SUCCESS)
		swap_one(a, 'y');
	return SUCCESS;
}

/*
	Sorts which_stack is specified, but only if containing exactly 3 elements.
	Returns -1 if not 3 elems, OR on subfunctions' ERRORs. 
	Reverse-rotates if rotate_one gets 'r' as its 1st argument, and just rotates if anything else e.g. ascii 'a' + ('r' - 'a') = 'r'.
	 // can/should this sorting be done using rotator, so I could also use rr, rrr, ss? Maybe with the help of another flag argument?
*/

int	sort_three(struct s_stack *stack, struct s_stack *other_stk)
{
	if (stack->top != 3)
		return (ERROR);
	if (is_sorted(stack) == SUCCESS)
		return (SUCCESS);
	if (find_min(stack) == 2 ||
		(stack->name == 'a' && stack->array[1] > stack->array[2]))
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
	if (other_stk->top == 2 && is_sorted(other_stk) != SUCCESS)
	{
		if (swapper(stack, other_stk, NULL) == ERROR)
			return (ERROR);
	}
	else if (swap_one(stack, 'y') == ERROR)
		return (ERROR);
	return (sort_three(stack, other_stk));
}

/*
	find_midvalue returns the middle value in the given stack. Use only when more than 3 numbers in stack
*/

int	find_midvalue(struct s_stack *stack)
{
	long	i;
	long	j;
	int		smaller_values;

	i = 0;
	j = 0;
	smaller_values = 0;
	if (stack->top < 4)
		return (ERROR);
	while (i != stack->top)
	{
		j = 0;
		smaller_values = 0;
		while (j != stack->top)
		{
			if (stack->array[i] > stack->array[j])
				smaller_values++;
			j++;
		}
		if (smaller_values == stack->top / 2) //  better to have less pb + pa operations, so sending less values to b like (stack->top - 1) / 2 is better than stack.top / 2
			return (stack->array[i]);
		i++;
	}
	return (ERROR);
}

/*
	find_min returns (int) index of the minimum value in the given stack.
*/

int find_min(struct s_stack *stack)
{
	long	i;
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
	// Maybe can also find negative stack index of closest non-sorted item to stack top, as that may be useful
*/

int is_sorted(struct s_stack *stack)
{
	unsigned int	i;

	i = stack->top - 1;
	if (stack->top == 0 || stack->top == 1)
		return (ERROR);
	while (i >= 1)//!=0 is better but needs testing
	{
		if (stack->name == 'a' && stack->array[i] >= stack->array[i - 1])
			return (ERROR);
		if (stack->name == 'b' && stack->array[i] <= stack->array[i - 1])
			return (ERROR);
		i--;
	}
	return (SUCCESS);
}

/*
	swap_one - does the actual swapping for swapper (sa or sb), and if print flag is 'p', prints out 'sa' or 'sb'
*/

int swap_one(struct s_stack *stack, char do_i_print)
{
	int	temp;

	if (stack->top == 0 || stack->top == 1)
		return (-1);
	temp = stack->array[stack->top - 1];
	stack->array[stack->top - 1] = stack->array[stack->top - 2];
	stack->array[stack->top - 2] = temp;
	if (do_i_print == 'y')
		return (printf("s%c\n", stack->name));
	return (0);
}
/*
	swapper - variadic function taking in two or three arguments, the last MUST BE NULL as a sentinel,
	otherwise undefined va_arg behaviour occurs. It calls swap_one with flag to print or not print its own operation.
	DISUSE VARIADIC FUNCTIONALITY, bc it is inconsistent in the project and char flag may do the job
*/

int swapper(struct s_stack *stack, ...)
{
	va_list(args);
	struct s_stack *stack_two;

	va_start(args, stack);
	stack_two = va_arg(args, struct s_stack *);
	if (stack_two != NULL)
	{
		if (swap_one(stack, 'n') == -1 || swap_one(stack_two, 'n') == -1) // maybe implement -1 and -2 handling
			return(va_end(args), ERROR);
		return(va_end(args), printf("ss\n"));
	}
	else
	{
		if (swap_one(stack, 'y') == -1)
			return (va_end(args), ERROR);
	}
	return (va_end(args), SUCCESS);
}

/*
	pusher - performs pa and pb functionality, printing out 'pa' or 'pb' accordingly.
	Returns -1 if did't execute the push and on error.
	MAYBE This could also benefit from using a char flag 'into_stack' so there's better UX when calling this function,
	as pusher('a', stack_a, stack_b) would be interpreted easier as push to a, and I wouldn't need to pay attention to stack order in brackets.
*/

int	pusher(struct s_stack *from_stack, struct s_stack *into_stack)
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
	rotate_one - does the actual rotating, reverse or normal, depending on char r_for_reverse flag being 'r' or not.
	Prints if do_i_print flag is 'y'. Returns 0 or positive num on success, and -1 on error.
*/

int	rotate_one(char r_for_reverse, struct s_stack *stack, char do_i_print) //passing char flag instead of int or using a variadic function seems more optimal
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

/* 
	Rotator rotates or reverse-rotates the specified stack (which_stck), or both if which_stck is 'r'.
	Returns -1 on error, and 0 or positive numbers on success.
	In rrr case, what if only ONE of rotations fails? Do I still print rrr and do i undo the other stack rotation? How can a stack rotation fail if not printing?
*/

int	rotator(char reverse, char which_stck, struct s_stack *a, struct s_stack *b)
{
    if (which_stck != a->name && which_stck != b->name && which_stck != 'r')
        return (ERROR);
	if (reverse == 'r')
	{
		if (which_stck == 'r')
		{
			rotate_one('r', a, 'n');
			rotate_one('r', b, 'n');
			return (printf("rrr\n"));
		}
		if (which_stck == a->name)
			return (rotate_one('r', a, 'y'));
		return (rotate_one('r', b, 'y'));
	}
	if (which_stck == 'r')
	{
		rotate_one('0', a, 'n');
		rotate_one('0', b, 'n');
		return (printf("rr\n"));
	}
	if (which_stck == a->name)
		return (rotate_one('0', a, 'y'));
	return (rotate_one('0', b, 'y'));
}
