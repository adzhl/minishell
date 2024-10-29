/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:15:59 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:38:04 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a copy of ’s1’ with the 
 * characters specified in ’set’ removed from the beginning and the end of 
 * the string.
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return The trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	trim_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trim_len = end - start;
	trim = malloc(trim_len + 1);
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, s1 + start, trim_len + 1);
	return (trim);
}

/*int	main(void)
{
	char const s1[] = "zzHello z Worldzz";
	char const set[] = "z";
	char *result;

	result = ft_strtrim(s1, set);
	printf("%s\n", result);
	free (result);
	return (0);
}*/
