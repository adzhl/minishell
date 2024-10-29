/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:25:28 by abinti-a          #+#    #+#             */
/*   Updated: 2024/08/06 14:19:32 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putuns(unsigned int n)
{
	char	digit;
	long	nb;
	int		len;

	len = 0;
	nb = n;
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	digit = nb % 10 + '0';
	write(1, &digit, 1);
	return (len + 1);
}
