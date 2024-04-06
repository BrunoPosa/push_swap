/*
	=========================
	|	 PUSH_SWAP UTILS	|
	=========================
*/

#include "push_swap.h"

/*
	?? popper - returns the top element from given stack and sets a zero in its place, reducing the top index.
	int *popper(struct s_stack *stack) ??
	{
	int temp = 0;
need to differentiate if the rvalue and value are the same somehow. maybe return boolean? or pointer instead of int
	if (stack->top == 0)
		return (0);
	temp = stack->array[stack->top - 1];
	stack->array[stack->top - 1] = 0;
	stack->top--;
	return(temp)
	}
*/

/* For now, initializer sets but also prints out what it sets. Later I plan for it to call InputValidator function.*/
int		initializer(int argc, char **argv, struct s_stack *stack_a, struct s_stack *stack_b)
{
    stack_a->name = 'a';
	stack_a->array = NULL;
	stack_a->maxsize = argc;
	stack_a->top = argc - 1; //*index of* the NEXT element in array
	stack_b->name = 'b';
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
		printf("element at i=%d (%d) goes to stack_a position=%d\n", i, stack_a->array[stack_a->top - i], stack_a->top - i);
		i++;
	}
    return(SUCCESS);
}

/*
	find_midvalue returns the middle value in the given stack. I think I should not use midvalue when less than 4 numbers in stack
*/
int	find_midvalue(struct s_stack *stack)
{
	unsigned int	i;
	unsigned int	j;
	int				k;

	i = 0;
	j = 0;
	k = 0;
	if (stack->top < 4)
		return (EMPTY);
	while (i != stack->top)
	{
		j = 0;
		k = 0;
		while (j != stack->top)
		{
			if (stack->array[i] > stack->array[j])
				k++;
			j++;
		}
		if (k == (stack->top - 1) / 2)
			return (stack->array[i]);
		i++;
	}
	// return (ERROR);
}

/*
	find_min returns unsigned int index of minimum value in the given stack.
*/
unsigned int find_min(struct s_stack *stack)
{
	unsigned int	i;
	unsigned int	min;

	i = 0;
	min = 0;
	if (stack->top == 0)
		return (EMPTY);
	while (i != stack->top)
	{
		if (stack->array[i] < stack->array[min])
			min = i;
		i++;
	}
	return (min);
}

/* If sorted, returns SUCCESS, if not, returns ERROR
//maybe can also find negative stack index of closest non-sorted item to stack top, as that may be useful */
int is_sorted(struct s_stack *stack)
{
	unsigned int	i;

	i = stack->top - 1;
	if (stack->top == 0 || stack->top == 1)
		return (-2);
	while (i >= 1)
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
	swapper_util - does the actual swapping for swapper (sa or sb), and if print flag is 'p', prints out 'sa' or 'sb'
*/
int swapper_util(struct s_stack *stack, char do_i_print)
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
	otherwise undefined va_arg behaviour occurs. It calls swapper_util with flag to print or not print its own operation.
*/
int swapper(struct s_stack *stack, ...)
{
	va_list(args);
	struct s_stack *second_stack;

	va_start(args, stack);
	second_stack = va_arg(args, struct s_stack *);
	if (second_stack != NULL)
	{
		if (swapper_util(stack, 'n') == -1 || swapper_util(second_stack, 'n') == -1) // maybe implement -1 and -2 handling
			return(va_end(args), -1);
		return(va_end(args), printf("ss\n"));
	}
	else
	{
		if (swapper_util(stack, 'y') == -1)
			return (va_end(args), -1);
	}
	return (va_end(args), 0); // SUCCESS
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

//=TESTING version= MAYBE I should not want 6-function functions (doing 6 operations ra rb rr rra rrb rrr in only 2 functions) #best_practice?
/*
	rotate_util - does the actual rotating, reverse or normal, depending on char r_for_reverse flag being 'r' or not.
	Prints if do_i_print flag is 'y'. Returns 0 or positive num on success, and -1 on error or -2 if nothing to rotate.
*/
int	rotate_util(char r_for_reverse, struct s_stack *stack, char do_i_print) //passing char flag instead of int or using a variadic function seems more optimal
{
	int temp;

	temp = 0;
	if (stack->top == 0 || stack->top == 1)
		return (-2); // not yet handling this in rotator, which already has the max 23 lines
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
		if(r_for_reverse == 'r')
			return (printf("rr%c\n", stack->name));
		return (printf("r%c\n", stack->name));
	}
	return (0);
}

/*Rotator rotates or reverse-rotates the specified stack, or both if which_stck is 'r'.*/
//returns -1 on error (maybe also -2 if nothing to rotate), and non-negative nums on success.
//BUT how do i differentiate between nothing to rotate and error? MAYBE return -2 if nothing to rotate, and -1 on error?
// in rrr, PRINT can't fail as I am not printing, and if only ONE of rotations fails, it's no biggie, still print rrr(?)

int	rotator(char reverse, char which_stck, struct s_stack *a, struct s_stack *b)
{
    if (which_stck != a->name && which_stck != b->name && which_stck != 'r')
        return (-printf("E"));
	if (reverse == 'r')
	{
		if (which_stck == 'r') // r means both rotate, and if this IF is true, they rotate in reverse, so 'rrr'
		{
			if (rotate_util('r', a, 'n') != -2 && rotate_util('r', b, 'n') != -2)
				return (printf("rrr\n"));
			return (-2);
		}
		if (which_stck == a->name)
			return (rotate_util('r', a, 'y'));
		return (rotate_util('r', b, 'y'));
	}
	if (which_stck == 'r')
	{
		if (rotate_util('o', a, 'n') != 0 || rotate_util('o', b, 'n') != 0) // to handle -2 and -1 rvalues, could I use a function pointer? or better logic?
			return (-1);
		return(printf("rr\n"));
	}
	if (which_stck == a->name)
		return (rotate_util('o', a, 'y'));
	return (rotate_util('o', b, 'y'));
}
