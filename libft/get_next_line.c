/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:47:51 by abinti-a          #+#    #+#             */
/*   Updated: 2024/07/12 10:32:12 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Find character c in string s
 */
static char	*ft_strchr(const char *s, int c)
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

/**
 * Read text from fd according to buffer size until fd is 0 (EOF)
 */
static char	*get_text(int fd)
{
	ssize_t	read_text;
	char	*storage;

	storage = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (storage == NULL)
		return (NULL);
	read_text = read(fd, storage, BUFFER_SIZE);
	if (read_text <= 0)
	{
		free(storage);
		return (NULL);
	}
	storage[read_text] = '\0';
	return (storage);
}

/**
 * Read until '\n' and append to buffer(if it exists)
 */
static char	*read_append_text(int fd, char *buffer)
{
	char	*combined;
	char	*storage;

	storage = get_text(fd);
	while (storage != NULL)
	{
		if (buffer == NULL)
			buffer = ft_strdup(storage);
		else
		{
			combined = ft_strjoin(buffer, storage);
			free(buffer);
			buffer = combined;
		}
		free(storage);
		if (ft_strchr(buffer, '\n'))
			break ;
		storage = get_text(fd);
	}
	return (buffer);
}

/**
 * Extract line until '\n' or '\0' if EOF
 */
static char	*extract_line(char **buffer)
{
	char	*line;
	char	*new_line;
	char	*update;

	if (*buffer == NULL || **buffer == '\0')
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	new_line = ft_strchr(*buffer, '\n');
	if (new_line != NULL)
	{
		line = ft_substr(*buffer, 0, new_line - *buffer + 1);
		update = ft_strdup(new_line + 1);
		free(*buffer);
		*buffer = update;
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

/**
 * 1. Check if fd & buffer size is valid
 * 2. Read line until '\n' is found or EOF
 * 3. Extract line until '\n' or '\0' if EOF
 * */
char	*get_next_line(int fd)
{
	char static	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_append_text(fd, buffer);
	line = extract_line(&buffer);
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("example.txt", O_RDONLY);

	char *result = get_next_line(fd);
	printf("%s", result);

	result = get_next_line(fd);
	printf("%s", result);

	result = get_next_line(fd);
	printf("%s", result);

	close(fd);
	return(0);
} */
