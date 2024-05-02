/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:10:15 by bposa             #+#    #+#             */
/*   Updated: 2024/05/02 14:54:17 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memmove(int *dst, const int *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0 || dst == src)
		return (dst);
	if (src < dst)
	{
		while (len > 0)
		{
			dst[len - 1] = src[len - 1];
			len--;
		}
		return (dst);
	}
	else
	{
		while (len > 0)
		{
			dst[i] = src[i];
			i++;
			len--;
		}
	}
	return (dst);
}
