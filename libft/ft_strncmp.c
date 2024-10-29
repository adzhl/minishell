/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:00:25 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:34:54 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief strncmp() function lexicographically compare the null-terminated 
 * strings s1 and s2. The strncmp() function compares not more than n 
 * characters.  Because strncmp() is designed for comparing strings rather 
 * than binary data,characters that appear after a `\0' character are not 
 * compared.
 * @return The strncmp() function return an integer greater 
 * than, equal to, or less than 0, according as the string s1 is greater 
 * than, equal to, or less than the string s2.  The comparison is done 
 * using unsigned characters, so that `\200' is greater than `\0'.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
