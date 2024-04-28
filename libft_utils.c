/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:47:12 by bposa             #+#    #+#             */
/*   Updated: 2024/04/28 20:58:56 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = malloc (ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i + 1 < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
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

static size_t	word_counter(char const *s, char c)
{
	size_t	word_count;
	int		word_flag;

	word_flag = 0;
	word_count = 0;
	if (!s)
	{
		return (0);
	}
	while (*s)
	{
		if (*s != c && word_flag == 0)
		{
			word_count++;
			word_flag = 1;
		}
		if (*s == c)
		{
			word_flag = 0;
		}
		s++;
	}
	return (word_count);
}

static char	**free_all(char **s, size_t i)
{
	while (i > 0)
	{
		i--;
		if (s[i])
		{
			free(s[i]);
		}
	}
	free(s);
	return (NULL);
}

static size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

static char	**array_filler(char const *src, char c, char **array)
{
	size_t	i;

	i = 0;
	while (*src)
	{
		while (*src && *src == c)
		{
			src++;
		}
		if (*src && *src != c)
		{
			array[i] = ft_substr(src, 0, word_len(src, c));
			if (!array[i])
			{
				return (free_all(array, i));
			}
			i++;
		}
		src += word_len(src, c);
	}
	array[i] = 0;
	return (array);
}


void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
int	ft_atoi(const char *s)
{
	long long	sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		sign = ',' - *s++;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10 && *s - '0' > LLONG_MAX % 10))
		{
			// deleted two lines here
			return (-1);
		}
		result = result * 10 + *s++ - '0';
	}
	return (sign * result);
}



void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	total_size;

	total_size = count * size;
	p = malloc(total_size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, total_size);
	return (p);
}

void	*my_memmove(int *dst, const int *src, size_t len)
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


char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	word_count;

	if (!s)
	{
		return (NULL);
	}
	i = 0;
	word_count = word_counter(s, c);
	arr = malloc((word_count + 1) * sizeof(char *));
	if (!arr)
	{
		return (NULL);
	}
	return (array_filler(s, c, arr));
}
