/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:57:41 by bposa             #+#    #+#             */
/*   Updated: 2024/04/27 22:13:17 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef ERROR
#  define ERROR -1
# endif

# include <stdlib.h>
# include <unistd.h> //?
# include <stdarg.h> //?
# include <limits.h>
# include <stdio.h>

typedef struct s_stack
{
	char	name;
	int		buckets;
	int		maxsize;
	int		top;
	int		*array;
}	t_stack;

int		ft_atoi(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*my_memmove(int *dst, const int *src, size_t len);
int		initializer(int argc, char **argv, t_stack *a, t_stack *b);
int		swap_one(t_stack *stack, char do_i_print);
int		pusher(t_stack *from_stack, t_stack *into_stack);
int		rotate_one(char r_for_reverse, t_stack *stack, char do_i_print);
int		rotate_cheaply(t_stack *stack, int splitvalue);
int		is_sorted(t_stack *stack);
int		find_min(t_stack *stack);
int		find_max(t_stack *stack);
int		find_splitvalue(t_stack *stack, int buckets);
int		sort_three(t_stack *stack, t_stack *other_stk);
int		stack_breaker(t_stack *a, t_stack *b);
int		insert_by_max(t_stack *a, t_stack *b);
int		loop_f(int n, t_stack *stack, char r, int (*f)(char, t_stack *, char));
int		count_values_under_splitvalue(t_stack *stack, int splitvalue);
int		split_into_sqrt(int number);

#endif