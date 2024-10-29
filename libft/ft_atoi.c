/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:58:15 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:18:47 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The atoi() function converts the initial portion of the string 
 * pointed to by str to int representation.
 *  */
int	ft_atoi(const char *str)
{
	int	negative;
	int	result;

	negative = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		negative = negative * -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * negative);
}

/* int main(void)
{
	const char str[] = "  -1241-13";

	printf("%d\n", ft_atoi(str));
	return (0);
} */
