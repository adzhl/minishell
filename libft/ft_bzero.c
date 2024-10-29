/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:42:45 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:17:25 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The bzero() function writes n zeroed bytes to the string s.  If n is
	zero, bzero() does nothing.
 *  */
void	ft_bzero(void *s, size_t n)
{
	char	*a;

	a = s;
	if (n == 0)
		return ;
	while (n > 0)
	{
		*a = 0;
		a++;
		n--;
	}
}
