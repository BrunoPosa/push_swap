
#include "push_swap.h"

void ft_bzero(void *s, size_t n)
{
	unsigned char *str;
	size_t i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void *ft_memset(void *b, int c, size_t len)
{
	size_t i;
	unsigned char *s;

	s = b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

int ft_atoi(const char *s)
{
	long long sign;
	long long result;

	sign = 1;
	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		sign = ',' - *s++;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && *s - '0' > LLONG_MAX % 10))
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		result = result * 10 + *s++ - '0';
	}
	return (sign * result);
}

void *ft_calloc(size_t count, size_t size)
{
	void *p;
	size_t total_size;

	total_size = count * size;
	p = malloc(total_size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, total_size);
	return (p);
}

/*
	OG memmove copies N BYTES of data, so when calling, the len has to be len * sizeof(data type) and I have to make sure it iterates as many times as precisely needed.
	Maybe pass to this the datatype?
*/
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
			dst[i] = src[i]; // 29.3. FIXED - THIS used to be typecasting to unsigned char. Spent 2-3 days on this, while travelling but nonetheless.
			i++;
			len--;
		}
	}
	return (dst);
}