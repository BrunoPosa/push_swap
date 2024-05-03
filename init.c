/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:07:58 by bposa             #+#    #+#             */
/*   Updated: 2024/05/03 15:26:20 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	initializer(int num_count, char **arg_list, t_stack *a, t_stack *b)
{
	int	i;

	i = 0;
	if (num_count == ERROR)
		return (ERROR);
	a->name = 'a';
	a->buckets = 2;
	a->maxsize = num_count + 1;
	a->top = num_count;
	a->array = (int *)ft_calloc(a->maxsize, sizeof(int));
	if (!a->array)
		return (ERROR);
	b->name = 'b';
	b->buckets = 2;
	b->maxsize = num_count + 1;
	b->top = 0;
	b->array = (int *)ft_calloc(b->maxsize, sizeof(int));
	if (!b->array)
		return (ERROR);
	while (arg_list[i] != NULL)
	{
		a->array[a->top - 1 - i] = ft_atoi(arg_list[i]);
		i++;
	}
	return (SUCCESS);
}

int	split_into_sqrt(int number)
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
