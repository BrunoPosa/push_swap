/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:34:25 by bposa             #+#    #+#             */
/*   Updated: 2024/05/03 15:02:27 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		sign = ',' - *s++;
	if (*s && (*s < '0' || *s > '9'))
		return (-1);
	while (*s && (*s >= '0' && *s <= '9'))
		result = result * 10 + *s++ - '0';
	if (*s && (*s < '0' || *s > '9'))
		return (-1);
	if (sign * result > 2147483647 || sign * result < -2147483648)
		return (-1);
	return (sign * result);
}
