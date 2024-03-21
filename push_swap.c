#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "push_swap.h"

/*
	=========================
	|	   LIBFT UTILS		|
	=========================
*/
void	ft_bzero(void *s, size_t n)
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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

int	ft_atoi(const char *s)
{
	long long	sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		sign = ',' - *s++;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10 && *s - '0' > LLONG_MAX % 10))
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		result = result * 10 + *s++ - '0';
	}
	return (sign * result);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	total_size;

	total_size = count * size;
	p = malloc(total_size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, total_size);
	return (p);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

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

/*
	sa - swap a - Swap the first 2 elements at the top of stack a.
	Do nothing if there is only one or no elements.
*/
int	top_swapper(struct s_stack *stack)
{
	int	temp;

	if (stack->top == 0 || stack->top == 1)
		return (0);
	temp = stack->array[stack->top];
	stack->array[stack->top] = stack->array[stack->top - 1];
	stack->array[stack->top - 1] = temp;

	puts("SA ended\n");
	return (EXIT_SUCCESS);
}

/*
	(push [to] a / push [to] b) - Take the first element at the top of src and put it
		at the top of dst. Do nothing if src is empty.
*/

/*
	push(int) - Adds an element to the stack.
*/
// int	push(int element, int *stack, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	//check for duplicates
// 	if (element == stack[0])
// 		return (EXIT_FAILURE);

// 	while (i < size)
// 	{
// 		stack[i + 1] ;
// 	}
// 	return(EXIT_SUCCESS);
// }


/*
	=========================
	|		  MAIN  		|
	=========================
*/
// returns non-zero on error
int main(int argc, char *argv[])
{
	struct s_stack	stack_a;
	int				i;
	// init
	stack_a.array = NULL;
	stack_a.maxsize = argc - 1;
	stack_a.top = stack_a.maxsize - 1; //used as the *index of* the top element in array
	i = 0;
	// sanity check
	if (argc < 2)
		return (-1);
	// allocate stack space and initialize to \0s, check malloc fails
	stack_a.array = (int *)ft_calloc(stack_a.maxsize, sizeof(int));
	if (!stack_a.array)
		return (printf("E"));
	// fill stack_a with arguments, converting them to integers
	while (stack_a.top >= 0)
	{
		stack_a.array[stack_a.top] = ft_atoi(argv[++i]);
		printf("element i=%d:%d to top:%d\n", i, stack_a.array[stack_a.top], stack_a.top);
		stack_a.top--;
	}
	stack_a.top = stack_a.maxsize - 1;

	// print arguments
	printf("top=%d, Arguments:\n", stack_a.top);
	while (stack_a.top >= 0)
	{
		printf("elem:%d at top:%d\n", stack_a.array[stack_a.top], stack_a.top);
		stack_a.top--;
	}
	printf("=Top: %d, size: %d\n___________________", stack_a.top, stack_a.maxsize);
	stack_a.top = stack_a.maxsize - 1;

	top_swapper(&stack_a);//this is swap_a actually
	// ==== PRINT ARRAY AFTER sa ====
	printf("After sa:\n");
	printf("top=%d, Arguments:\n", stack_a.top);
	while (stack_a.top >= 0)
	{
		printf("elem:%d at top:%d\n", stack_a.array[stack_a.top], stack_a.top);
		stack_a.top--;
	}
	printf("=Top: %d, size: %d\n___________________", stack_a.top, stack_a.maxsize);
	stack_a.top = stack_a.maxsize - 1;
	// Push_Swap logic here
	// push_swap(&input_stack, size);

	// clean up
	// free(stack_a.stack);
	return (EXIT_SUCCESS);
}

