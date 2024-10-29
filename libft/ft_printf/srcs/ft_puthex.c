/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:43:51 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/20 11:25:07 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_puthex(unsigned long n, char format)
{
	static int	len;
	char		*base;

	if (format == 'x')
		base = "0123456789abcdef";
	if (format == 'X')
		base = "0123456789ABCDEF";
	len = 0;
	if (n >= 16)
		len = ft_puthex(n / 16, format);
	len = len + ft_putchar(base[n % 16]);
	return (len);
}

/* int	main(void)
{
	unsigned long num = 123456;
	int len;

	len = ft_puthex(num, 'x');
	printf("\nLength: %d\n", len);

	len = ft_puthex(num, 'X');
	printf("\nLength: %d\n", len);

	return (0);
} */