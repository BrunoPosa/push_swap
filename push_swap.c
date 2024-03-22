#include <stdio.h>
#include <stdlib.h>
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

void *ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0 || dst == src)
		return (dst);
	if (src < dst)
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
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

int swapper(struct s_stack *stack, int n1, int n2)
{
	int temp;

	if (stack->top == 0 || stack->top == 1)
		return (-1);
	temp = stack->array[n1];
	stack->array[n1] = stack->array[n2];
	stack->array[n2] = temp;
	return (0); // SUCCESS
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
int	pusher(struct s_stack *from, struct s_stack *into)
{
	if (from->top == 0)
		return (-1);
	into->array[into->top] = from->array[from->top - 1];
	into->top++;
	from->top--;
	from->array[from->top] = 0;
	return (0);
}

/*
	sa - swap a - Swap the first 2 elements at the top of stack a.
	Do nothing if there is only one or no elements.
*/
int sa(struct s_stack *ptr)
{
	if (swapper(ptr, ptr->top - 1, ptr->top - 2) == 0)
	{
		puts("sa\n");
		return (0); // SUCCESS
	}
	else
		return (-1);
}

/*
	sb - swap b - Swap the first 2 elements at the top of stack b.
	Do nothing if there is only one or no elements.
*/
int sb(struct s_stack *ptr)
{
	if (swapper(ptr, ptr->top - 1, ptr->top - 2) == 0)
	{
		puts("sb\n");
		return (0); // SUCCESS
	}
	else
		return (-1);
}

/*
	ss - sa and sb at the same time.
*/
int ss(struct s_stack *ptr_a, struct s_stack *ptr_b)
{
	if (sa(ptr_a) == 0 && sb(ptr_b) == 0)
	{
		puts("ss\n");
		return (0); // SUCCESS
	}
	else
		return (-1);
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
	stack_a.array = NULL;
	stack_a.maxsize = argc;
	stack_a.top = argc - 1; //*index of* the NEXT element in array
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

	// TEST print from top to bottom of stack a
	// ------------------------------------------------------
	// i = 1;
	// printf("top=%d, printout:\n", stack_a.top);
	// while (stack_a.top - i >= 0)
	// {
	// 	printf("elem:%d at stack position:%d\n", stack_a.array[stack_a.top - i], stack_a.top - i);
	// 	i++;
	// }
	// printf("=Top: %d, size: %d\n___________________\n", stack_a.top, stack_a.maxsize);
	// ------------------------------------------------

	// Push_Swap algo logic here

	// clean up
	free(stack_a.array);
	free(stack_b.array);
	return (EXIT_SUCCESS);
}
