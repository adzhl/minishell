/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:27:03 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:19:00 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the integer ’n’ to the given file descriptor.
 */
void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = nb * -1;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	digit = nb % 10 + '0';
	write(fd, &digit, 1);
}

/* int	main(void)
{
	ft_putnbr_fd(1234, 1);
	ft_putnbr_fd(-8653, 1);
	return (0);
} */