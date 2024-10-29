/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:59:20 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:36:12 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strnstr() function locates the first occurrence of the 
 * null-terminated string needle in the string haystack, where not more than 
 * len characters are searched.  Characters that appear after a `\0' 
 * character are not searched.
 * @return If needle is an empty string, haystack is returned; if needle 
 * occurs nowhere in haystack, NULL is returned; otherwise a pointer to the 
 * first character of the first occurrence of needle is returned.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	size_t	i;

	n_len = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (needle[n_len] != '\0')
		n_len++;
	if (len == 0)
		return (NULL);
	while (*haystack != '\0' && len >= n_len)
	{
		i = 0;
		while (i < n_len && haystack[i] == needle[i])
			i++;
		if (i == n_len)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
