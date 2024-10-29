/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:47:31 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:37:01 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strrchr() function locates the last occurrence of c 
 * (converted to a char) in the string pointed to by s.  The terminating 
 * null character is considered to be part of the string; therefore if c 
 * is `\0', the functions locate the terminating `\0'.
 * @return Returns a pointer to the located character, or NULL if the 
 * character does not appear in the string.
 */
char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)last);
}
