/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:23:43 by bposa             #+#    #+#             */
/*   Updated: 2024/05/03 14:46:52 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_hex(unsigned long int n, int *err, const char *digits)
{
	int	count;

	count = 0;
	if (n >= 0x10)
	{
		count += put_hex(n / 0x10, err, digits);
	}
	if (*err != -1)
		*err = (int)write(1, &digits[n % 0x10], sizeof(char));
	if (*err == -1)
		return (-1);
	count++;
	return (count);
}
