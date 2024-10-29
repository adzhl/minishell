/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:12 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:37:19 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The memcpy() function copies n bytes from memory area src to 
 * memory area dst.  If dst and src overlap, behavior is undefined.
 * @return The memcpy() function returns the original value of dst.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;	
	const char	*s;

	if (dst == NULL && src == NULL)
		return (dst);
	d = (char *)dst;
	s = (const char *)src;
	while (n > 0)
	{
		*d = *s;
		s++;
		d++;
		n--;
	}
	return (dst);
}
