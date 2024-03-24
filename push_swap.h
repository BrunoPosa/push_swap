/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:57:41 by bposa             #+#    #+#             */
/*   Updated: 2024/03/24 13:33:46 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>

struct s_stack
{
	char	name;
	int		maxsize; //size (length) of the given input, stack_a
	int		top; //(SIZE of the current array) indicates index of next insertion
	int		*array; //pointer to given input arrray
};

#endif