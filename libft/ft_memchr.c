/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:47:38 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:35:55 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The memchr() function locates the first occurrence of c 
 * (converted to an unsigned char) in string s.
 * @return The memchr() function returns a pointer to the byte located, 
 * or NULL if no such byte exists within n bytes.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*z;
	unsigned char		d;

	z = s;
	d = (char)c;
	while (n > 0)
	{
		if (*z == d)
			return ((void *)z);
		z++;
		n--;
	}
	return (NULL);
}
