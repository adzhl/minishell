/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:18:00 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:23:17 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The	strdup() function allocates sufficient memory for a copy of the
string s1, does the copy, and returns a pointer to it.  The pointer may
subsequently be used as an argument to the function	free(3).
 *  */
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*p;
	size_t	i;

	len = 0;
	while (s1[len] != '\0')
		len++;
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/*int main()
{
	const char *ori = "Hello, world!";
	char *dup;

	dup = ft_strdup(ori);

	printf("Original string: %s\n", ori);
	printf("Duplicate string: %s\n", dup);

	free(dup);

	return (0);
}*/
