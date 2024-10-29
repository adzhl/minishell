/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:43:06 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:38:44 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The memcmp() function compares byte string s1 against byte string 
 * s2. Both strings are assumed to be n bytes long.
 * @return returns zero if the two strings are identical, otherwise returns 
 * the difference between the first two differing bytes. 
 * Zero-length strings are always identical.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_char;
	const unsigned char	*s2_char;

	s1_char = s1;
	s2_char = s2;
	while (n > 0)
	{
		if (*s1_char != *s2_char)
			return (*s1_char - *s2_char);
		s1_char++;
		s2_char++;
		n--;
	}
	return (0);
}
