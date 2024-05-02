/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:46:12 by bposa             #+#    #+#             */
/*   Updated: 2024/05/02 14:52:35 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	malloc_len;

	i = 0;
	malloc_len = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0 || s[0] == '\0')
	{
		return (ft_strdup(""));
	}
	if (len < ft_strlen(&s[start]))
	{
		malloc_len = len + 1;
	}
	else
	{
		malloc_len = ft_strlen(&s[start]) + 1;
	}
	str = malloc(malloc_len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s[start], malloc_len);
	return (str);
}
