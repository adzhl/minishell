/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:26:51 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:22:09 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strchr() function locates the first occurrence of c 
 * (converted to a char) in the string pointed to by s.  The terminating 
 * null character is considered to be part of the string; therefore if c 
 * is `\0', the functions locate the terminating `\0'.
 * @return Returns a pointer to the located character, or NULL if the 
 * character does not appear in the string.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
