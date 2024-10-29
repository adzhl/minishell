/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:19:43 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:20:54 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns an array of strings 
 * obtained by splitting ’s’ using the character ’c’ as a delimiter. 
 * The array must end with a NULL pointer.
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split.
 * NULL if the allocation fails.
 */
static size_t	count_word(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static void	free_word(size_t len, char **word)
{
	while (len > 0)
	{
		len--;
		free(word[len]);
	}
	free(word);
}

static size_t	make_word(char **word, char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			len = word_len(s, c);
			word[i] = ft_substr(s, 0, len);
			if (word[i] == NULL)
			{
				free_word(i, word);
				return (0);
			}
			s = s + len;
			i++;
		}
	}
	word[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**word;

	if (s == NULL)
		return (NULL);
	word = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (word == NULL)
		return (NULL);
	if (make_word(word, s, c) == 0)
	{
		free(word);
		return (NULL);
	}
	return (word);
}

/* int	main(void) {
	char const s[] = "Hello My Name Is Adya";
	char c = ' ';
	char **result = ft_split(s, c);
	int i = 0;
	while(result[i] != NULL)
	{
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
 */
