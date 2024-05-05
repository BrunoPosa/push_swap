/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:52:47 by bposa             #+#    #+#             */
/*   Updated: 2024/04/27 18:52:47 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	end_free(char do_i_print_error, void *one, void *two, char **args)
{
	int	i;

	i = 0;
	if (one)
		free(one);
	if (two)
		free(two);
	if (args)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	if (do_i_print_error == 'y')
		write(2, "Error\n", 6 * sizeof(char));
	return (ERROR);
}

int	main(int argc, char *argv[])
{
	t_stack	a;
	t_stack	b;
	char	**str_args;

	str_args = NULL;
	if (argc < 2)
		return (SUCCESS);
	if (argc == 2 && count_disconnected_spaces(argv[1]) > 0)
	{
		str_args = ft_split(argv[1], ' ');
		if (str_args == NULL)
			return (end_free('y', a.array, b.array, str_args));
		if (initializer(input_validator(str_args), str_args, &a, &b) != SUCCESS)
			return (end_free('y', a.array, b.array, str_args));
	}
	else
	{
		if (initializer(input_validator(argv + 1), argv + 1, &a, &b) != SUCCESS)
			return (end_free('y', a.array, b.array, str_args));
	}
	if (core_logic(&a, &b) == ERROR)
		return (end_free('y', a.array, b.array, str_args));
	end_free('n', a.array, b.array, str_args);
	return (SUCCESS);
}
