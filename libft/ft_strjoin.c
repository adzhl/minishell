/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:49:27 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:25:20 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the 
 * result of the concatenation of ’s1’ and ’s2’.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string. NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	total;
	size_t	s1_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	total = s1_len + ft_strlen(s2) + 1;
	new = malloc(total);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s1, total);
	ft_strlcpy(new + s1_len, s2, total - s1_len);
	return (new);
}

/*int main() {
    char const s1[] = "Hello, ";
    char const s2[] = "World!";
    char *new;

    new = ft_strjoin(s1, s2);
    printf("%s\n", new);

    free(new);
    return 0;
}*/
