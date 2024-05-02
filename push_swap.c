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
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	t_stack	a;
	t_stack	b;
	char	**str_args;

	str_args = NULL;
	if (argc < 2 || (argc == 2 && argv[1][0] == '\0'))
		return (ERROR);
	if (argc == 2 && count_disconnected_spaces(argv[1]) > 0)
	{
		str_args = ft_split(argv[1], ' ');
		if (initializer(input_validator(str_args), str_args, &a, &b) != SUCCESS)
			return (write(2, "Error\n", 6 * sizeof(char)));
	}
	else
	{
		if (initializer(input_validator(argv + 1), argv + 1, &a, &b) != SUCCESS)
			return (write(2, "Error\n", 6 * sizeof(char)));
	}
	if (core_logic(&a, &b) == ERROR)
		return (write(2, "Error\n", 6 * sizeof(char)));
	free(a.array);
	free(b.array);
	return (SUCCESS);
}
