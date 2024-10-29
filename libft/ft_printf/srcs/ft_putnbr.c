/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:30:06 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/19 18:12:45 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putnbr(int n)
{
	char	digit;
	long	nb;
	int		len;

	len = 0;
	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		len++;
	}
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	digit = nb % 10 + '0';
	write(1, &digit, 1);
	return (len + 1);
}

/* int main(void)
{
	int n = -123;

	int result = ft_putnbr(n);
	printf("\n");
	printf("%d\n", result);
	return (0);
} */