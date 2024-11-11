/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:48:51 by etien             #+#    #+#             */
/*   Updated: 2024/11/11 11:37:31 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will fork a child process to handle the heredoc.
// The child process will accumulate the input into the pipe's write end.
// The parent process will wait for the child to terminate to read the input
// from the pipe's read end.
void	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;

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
		read_hd_input(pipefd[0]);
		close(pipefd[READ]);
		wait(NULL);
	}
}

// The child process will extract lines from STDIN and write
// them to the pipe until the EOF delimiter is encountered.
void	collect_hd_input(int pipefd[2], char *delimiter)
{
	char	*line;

	close(pipefd[READ]);
	while (extract_line(&line) > 0)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
			break ;
		write(pipefd[WRITE], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipefd[WRITE]);
	exit(EXIT_SUCCESS);
}

// This function will read input from stdout character by character
// into a buffer until a newline character is encountered,
// then the line pointer passed in as an argument will point to
// buffer to update line in the here_doc function.
int	extract_line(char **line)
{
	char	*buffer;
	char	c;
	int		i;
	int		bytes_read;

	buffer = ft_calloc(256, sizeof(char));
	if (!buffer)
		return (-1);
	i = 0;
	bytes_read = read(0, &c, 1);
	while (bytes_read > 0)
	{
		buffer[i] = c;
		i++;
		if (c == '\n')
			break ;
		bytes_read = read(0, &c, 1);
	}
	*line = buffer;
	return (bytes_read);
}



