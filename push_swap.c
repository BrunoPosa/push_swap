#include <stdlib.h>
#include <unistd.h> //?
#include <stdarg.h> //?
#include <stdio.h>
#include <limits.h>
#include "push_swap.h"

/*
	=========================
	|	   LIBFT UTILS		|
	=========================
*/
void ft_bzero(void *s, size_t n)
{
	unsigned char *str;
	size_t i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void *ft_memset(void *b, int c, size_t len)
{
	size_t i;
	unsigned char *s;

	s = b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

int ft_atoi(const char *s)
{
	long long sign;
	long long result;

	sign = 1;
	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		sign = ',' - *s++;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && *s - '0' > LLONG_MAX % 10))
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		result = result * 10 + *s++ - '0';
	}
	return (sign * result);
}

void *ft_calloc(size_t count, size_t size)
{
	void *p;
	size_t total_size;

	total_size = count * size;
	p = malloc(total_size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, total_size);
	return (p);
}
// 		assumption that dest is bigger than src as has a larger array index
// working with an int array is different than strings!
//			  &stack->array[1] &stack->array[0]  stack->top /5
void	*my_memmove(int *dst, const int *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0 || dst == src)
		return (dst);
	if (src < dst)
	{
		while (len > 0)
		{
			dst[len - 1] = src[len - 1];
			len--;
		}
		return (dst);
	}
	else
	{
		while (len > 0)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
			len--;
		}
	}
	return (dst);
}


/*
	=========================
	|	 PUSH_SWAP UTILS	|
	=========================
*/

/*
	printer - takes two letters as arguments and prints them along with a \n, returning -1 on errors
	MAYBE use FT_PRINTF instead of this ;)
*/
ssize_t	printer(char operation_ch, char stack_name_ch)
{
	if (write(1, &operation_ch, sizeof(char)) == -1)
		return (-1);
	if (write(1, &stack_name_ch, sizeof(char)) == -1)
		return (-1);
	if (write(1, "\n", sizeof(char)) == -1)
		return (-1);
	return(0); // SUCCESS
}

/*
	swapper_util - does the actual swapping for swapper (sa or sb), and if print flag is up, prints out 'sa' or 'sb'
*/
int swapper_util(struct s_stack *stack, int print_flag)
{
	int	temp;

	if (stack->top == 0 || stack->top == 1)
		return (-1);
	temp = stack->array[stack->top - 1];
	stack->array[stack->top - 1] = stack->array[stack->top - 2];
	stack->array[stack->top - 2] = temp;
	if (print_flag == 1)
		return (printer('s', stack->name)); // replace w/ ft_printf
	return (0);
}
/*
	swapper - variadic function taking in two or three arguments, the last MUST BE NULL as a sentinel,
	otherwise undefined va_arg behaviour occurs.
*/
int swapper(struct s_stack *stack, ...)
{
	va_list(args);
	struct s_stack *second_stack;

	va_start(args, stack);
	second_stack = va_arg(args, struct s_stack *);
	if (second_stack != NULL)
	{
		if (swapper_util(stack, 0) == -1 || swapper_util(second_stack, 0) == -1)
			return(va_end(args), -1);
		printf("ss\n"); // ft_printf !!
	}
	else
	{
		if (swapper_util(stack, 1) == -1)
			return (va_end(args), -1);
	}
	return (va_end(args), 0); // SUCCESS
}
//	?? popper - returns the top element from given stack and sets a zero in its place, reducing the top index.
//	int *popper(struct s_stack *stack) ??
//	{
//	int temp = 0;
//need to differentiate if the rvalue and value are the same somehow. maybe return boolean? or pointer instead of int
//	if (stack->top == 0)
// 		return (0);
//	temp = stack->array[stack->top - 1];
//	stack->array[stack->top - 1] = 0;
//	stack->top--;
//	return(temp)
// 	}

/*
	pusher - performs pa and pb functionality, printing out 'pa' or 'pb' accordingly.
	Returns -1 if did't execute the push and on error.
*/
int	pusher(struct s_stack *from_stack, struct s_stack *into_stack)
{
	if (from_stack->top == 0)
		return (-1);
	into_stack->array[into_stack->top] = from_stack->array[from_stack->top - 1];
	into_stack->top++;
	from_stack->top--;
	from_stack->array[from_stack->top] = 0;
	if (printer('p', into_stack->name) == -1)
		return (-1);
	return (0);
}

int	rotator(struct s_stack *stack)
{
	int temp;

	if (stack->top == 0 || stack->top == 1)
		return (-1);
	temp = stack->array[stack->top - 1];
	my_memmove(&stack->array[1], &stack->array[0], stack->top);
	stack->array[0] = temp;
	if (printer('r', stack->name) == -1)
		return (-1);
	return (0); // SUCCESS
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
	struct s_stack stack_b;
	int i;
	// init
	stack_a.name = 'a';
	stack_a.array = NULL;
	stack_a.maxsize = argc;
	stack_a.top = argc - 1; //*index of* the NEXT element in array
	stack_b.name = 'b';
	stack_b.array = NULL;
	stack_b.maxsize = argc;
	stack_b.top = 0;
	i = 1;
	// sanity check
	if (argc < 2)
		return (-1);
	// allocate stacks space and initialize to \0s, check malloc fails
	stack_a.array = (int *)ft_calloc(stack_a.maxsize, sizeof(int));
	if (!stack_a.array)
		return (printf("E"));
	stack_b.array = (int *)ft_calloc(stack_b.maxsize, sizeof(int));
	if (!stack_b.array)
		return (printf("E"));
	// fill stack_a with arguments, converting them to integers
	while (stack_a.top - i >= 0)
	{
		stack_a.array[stack_a.top - i] = ft_atoi(argv[i]);
		printf("element at i=%d (%d) goes to stack_a position=%d\n", i, stack_a.array[stack_a.top - i], stack_a.top - i);
		i++;
	}

	pusher(&stack_a, &stack_b);
	pusher(&stack_a, &stack_b);
	swapper(&stack_b, NULL); // must end with NULL

	// PRINT TEST from top to bottom of stack a
	// ------------------------------------------------------
	i = 1;
	printf("printout STACK A: top=%d\n", stack_a.top);
	while (stack_a.top - i >= 0)
	{
		printf("elem:%d at stack position:%d\n", stack_a.array[stack_a.top - i], stack_a.top - i);
		i++;
	}
	printf("=Top: %d, size: %d\n___________________\n", stack_a.top, stack_a.maxsize);
	// ------------------------------------------------


	// PRINT TEST from top to bottom of stack b
	// ------------------------------------------------------
	i = 1;
	printf("printout STACK B: top=%d\n", stack_b.top);
	while (stack_b.top - i >= 0)
	{
		printf("elem:%d at stack position:%d\n", stack_b.array[stack_b.top - i], stack_b.top - i);
		i++;
	}
	printf("=Top: %d, size: %d\n___________________\n", stack_b.top, stack_b.maxsize);
	// ------------------------------------------------------





	// Push_Swap algo logic here

	// clean up
	free(stack_a.array);
	free(stack_b.array);
	return (EXIT_SUCCESS);
}
