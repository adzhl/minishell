/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:46:27 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:29:21 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a string representing 
 * the integer received as an argument. Negative numbers must be handled.
 * @param n the integer to convert.
 * @return The string representing the integer. NULL if the allocation fails.
 */
static size_t	count_num(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*alloc_size(int n)
{
	size_t	len;
	char	*len_size;

	len = count_num(n);
	len_size = malloc(((len) + 1) * (sizeof(char)));
	if (len_size == NULL)
		return (NULL);
	return (len_size);
}

static void	condition(char *str, int n, size_t len)
{
	int		sign;
	size_t	i;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		str[0] = '-';
	}
	str[len] = '\0';
	i = len - 1;
	while (n != 0)
	{
		str[i] = '0' + (sign * (n % 10));
		n = n / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*converted;
	size_t	len;

	converted = alloc_size(n);
	if (converted == NULL)
		return (NULL);
	len = count_num(n);
	if (n == 0)
	{
		converted[0] = '0';
		converted[1] = '\0';
	}
	else
		condition(converted, n, len);
	return (converted);
}

/*int	main(void)
{
	char *s1 = ft_itoa(28963);
	char *s2 = ft_itoa(0);
	char *s3 = ft_itoa(-9873);

	printf("%s\n", s1);
	printf("%s\n", s2);
	printf("%s\n", s3);

	free(s1);
	free(s2);
	free(s3);
	return (0);
}*/