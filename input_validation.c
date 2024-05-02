/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:14:07 by bposa             #+#    #+#             */
/*   Updated: 2024/05/02 17:14:11 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	validate input arguments and return count of valid numbers in argv or ERROR
*/
int	input_validator(char **arg_list)
{
	int	valid_number_count;

	valid_number_count = 0;
	if (substring_validator(arg_list, &valid_number_count) == ERROR)
		return (ERROR);
	if (has_duplicates(arg_list) == SUCCESS)
		return (ERROR);
	return (valid_number_count);
}

int	substring_validator(char **input_strings, int *valid_number_count)
{
	if (input_strings == NULL)
		return (ERROR);
	while (*input_strings != NULL)
	{
		if (str_is_valid_number(*input_strings) == SUCCESS)
		{
			*valid_number_count += 1;
			input_strings++;
		}
		else
			return (ERROR);
	}
	return (SUCCESS);
}

int	str_is_valid_number(char *s)
{
	int	n;

	n = ft_atoi(s);
	if (is_just_spacenumbers(s) != SUCCESS)
		return (ERROR);
	if (n == -1)
	{
		if (ft_strlen(s) == 2 && s[0] == '-' && s[1] == '1')
			return (SUCCESS);
		return (ERROR);
	}
	if (n == 0 && s[ft_strlen(s) - 1] != '0')
		return (ERROR);
	return (SUCCESS);
}

int	has_duplicates(char **number_set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (number_set[i] != NULL)
	{
		j = 0;
		while (number_set[j] != NULL)
		{
			if (i != j && ft_atoi(number_set[i]) == ft_atoi(number_set[j]))
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (ERROR);
}

int	is_just_spacenumbers(char *s)
{
	while (*s != '\0')
	{
		if ((*s >= '0' && *s <= '9') || *s == ' ' || *s == '-' || *s == '+')
			s++;
		else
			return (ERROR);
	}
	return (SUCCESS);
}
