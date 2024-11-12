/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:48:51 by etien             #+#    #+#             */
/*   Updated: 2024/11/12 11:12:22 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will fork a child process to handle the heredoc.
// The child process will accumulate the input into the pipe's write end.
// The parent process will wait for the child to terminate to read the input
// from the pipe's read end.
char	*handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	char	*hd_content;
	bool	expand_hd;

	hd_content = NULL;
	expand_hd = true;
	check_delimiter(&delimiter, &expand_hd);
	if (pipe(pipefd) < 0)
		perror(PIPE_ERR);
	pid = fork();
	if (pid < 0)
		perror(FORK_ERR);
	else if (pid == 0)
		collect_hd_input(pipefd, delimiter);
	else
	{
		close(pipefd[WRITE]);
		read_hd_input(&hd_content, pipefd[0]);
		close(pipefd[READ]);
		wait(NULL);
	}
	if (expand_hd)
		hd_content = expand_heredoc(hd_content);
	return (hd_content);
}

// The child process will extract lines from STDIN via the
// readline prompt and write them to the pipe until the EOF
// delimiter is encountered.
// Readline does not explicitly include the newline in the
// returned buffer, so we have to manually add it in the pipe.
void	collect_hd_input(int pipefd[2], char *delimiter)
{
	char	*hd_line;

	close(pipefd[READ]);
	while (1)
	{
		hd_line = readline("> ");
		if (!hd_line || (ft_strcmp(hd_line, delimiter) == 0))
		{
			if (hd_line)
				free(hd_line);
			break ;
		}
		write(pipefd[WRITE], hd_line, ft_strlen(hd_line));
		write(pipefd[WRITE], "\n", 1);
		free(hd_line);
	}
	close(pipefd[WRITE]);
	exit(EXIT_SUCCESS);
}

// This function will read the hd_input out from the pipe
// into a buffer. A buffer is necessary because the total size of
// data in the pipe is not known in advance.
// Memory is dynamically allocated according to the total number of
// bytes read and assigned to hd_content.
// The hd_input is then copied over from the buffer to hd_content.
// If the pipe's contents exceed the size of the buffer, the buffer
// will be refreshed with the remaining pipe data and the memory for
// hd_content will be reallocated.
// The function will ensure that hd_content is null_terminated.
void	read_hd_input(char **hd_content, int pipefd_read)
{
	char	buffer[1024];
	char	*temp;
	int		bytes_read;
	int		total_bytes;

	total_bytes = 0;
	bytes_read = read(pipefd_read, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		temp = malloc(total_bytes + bytes_read + 1);
		if (!temp)
			perror(MALLOC_ERR);
		if (*hd_content)
		{
			ft_memcpy(temp, *hd_content, total_bytes);
			free(*hd_content);
		}
		ft_memcpy(temp + total_bytes, buffer, bytes_read);
		total_bytes += bytes_read;
		temp[total_bytes] = 0;
		*hd_content = temp;
		bytes_read = read(pipefd_read, buffer, sizeof(buffer));
	}
}

// This function will expand the heredoc.
// Heredoc expansion completely disregards quotes (treats them as any other character)
// and only substitutes in variables.
// A local pointer is created so that we can retain the starting pointer
// to the original heredoc to free it.
char *expand_heredoc(char *heredoc)
{
	char *expanded_heredoc;
	char *s;

	s = heredoc;
	expanded_heredoc = ft_strdup("");
	while (*s)
	{
		if (*s == '$')
			expanded_heredoc = sub_in_var(&s, expanded_heredoc);
		else
			expanded_heredoc = append_str(&s, expanded_heredoc, HEREDOC, '\0');
	}
	free(heredoc);
	return (expanded_heredoc);
}

// This function will check the delimiter for closed quotes.
// If there are quotes, they will be removed and expand_hd will
// be set to false to prevent heredoc expansion.
void check_delimiter(char **delimiter, bool *expand_hd);
{



}

// This function will compare two strings.
// If they are identical, it will return 0. Otherwise, it will return
// the ASCII value difference of the last compared characters.
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}