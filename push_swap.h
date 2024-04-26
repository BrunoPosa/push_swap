/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:57:41 by bposa             #+#    #+#             */
/*   Updated: 2024/04/26 18:24:31 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h> //?
#include <stdarg.h> //?
#include <limits.h>
#include <stdio.h>

struct s_stack
{
	char	name;	 // Arnold: change this from 'name' which sounds inconsequential into 'order' to clarify the ascending/descending property
	int		maxsize; // DO I REALLY NEED THIS?  size (length) of the given input, stack_a.
	int		top;	 //(SIZE of the current array) indicates index of next insertion
	int		*array;	 // pointer to given input arrray
};

// int		ft_printf();
int		ft_atoi(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*my_memmove(int *dst, const int *src, size_t len);

size_t	my_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		initializer(int argc, char **argv, struct s_stack *stack_a, struct s_stack *stack_b); // NORM LINE TOO LONG
int		swapper(struct s_stack *stack, ...); //passing char flag instead of int or using a variadic function is more optimal
int		swap_one(struct s_stack *stack, char do_i_print);
int		pusher(struct s_stack *from_stack, struct s_stack *into_stack);
int		rotator(char reverse, char which_stck, struct s_stack *a, struct s_stack *b);
int		rotate_one(char r_for_reverse, struct s_stack *stack, char do_i_print);
int		is_sorted(struct s_stack *stack);
int		find_min(struct s_stack *stack);
int		find_max(struct s_stack *stack);
int		find_splitvalue(struct s_stack *stack);
int		sort_three(struct s_stack *stack, struct s_stack *other_stk);
int		sort_five(struct s_stack *a, struct s_stack *b);
int		stack_breaker(struct s_stack *a, struct s_stack *b);
int		insert_by_max(struct s_stack *a, struct s_stack *b);
int		cheaper_rotate(struct s_stack *stack, int splitvalue);
int		loop(int n, struct s_stack *stack, char r, int (*f)(char, struct s_stack *, char));

#ifndef SUCCESS
# define SUCCESS 0
#endif

#ifndef ERROR
# define ERROR -1
#endif

#ifndef EMPTY
# define EMPTY -2
#endif

#endif