/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:53:46 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/19 17:25:51 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putstr(char *s)
{
	int	len;

	if (s == NULL)
		return (write(1, "(null)", 6));
	len = ft_strlen(s);
	while (*s != '\0')
	{
		write(1, s, 1);
		s++;
	}
	return (len);
}

/* int main(void)
{
	char s[] = "Heya HEy";

	int result = ft_putstr(s);
	printf("\n");
	printf("%d\n", result);
	return (0);
} */