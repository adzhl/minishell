/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:48:51 by etien             #+#    #+#             */
/*   Updated: 2024/12/16 16:57:44 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will fork a child process to handle the heredoc.
// The child process will accumulate the input into the pipe's write end.
// The parent process will wait for its child to terminate to read the input
// from the pipe's read end.
char	*handle_heredoc(char **eof, t_mshell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	char	*hd_content;
	bool	expand_hd;
	int		status;

	hd_content = ft_strdup("");
	expand_hd = true;
	check_delimiter(eof, &expand_hd);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
		collect_heredoc_input(pipefd, *eof);
	else if (pid > 0)
	{
		close(pipefd[WRITE]);
		read_heredoc_input(&hd_content, pipefd[0]);
		close(pipefd[READ]);
		waitpid(pid, &status, 0);
		handle_signal_heredoc(shell, status);
	}
	if (expand_hd)
		hd_content = expand_heredoc(hd_content, shell);
	return (hd_content);
}

// The child process will extract lines from STDIN via the
// readline prompt and write them to the pipe until the EOF
// delimiter is encountered.
// Readline does not explicitly include the newline in the
// returned buffer, so we have to manually add it in the pipe.
void	collect_heredoc_input(int pipefd[2], char *eof)
{
	char	*hd_line;

	signal(SIGINT, SIG_DFL);
	close(pipefd[READ]);
	while (1)
	{
		hd_line = readline("> ");
		if (!hd_line)
		{
			ft_putendl_fd(HEREDOC_ERR, STDOUT_FILENO);
			break ;
		}
		if (ft_strcmp(hd_line, eof) == 0)
		{
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
// The function will ensure that hd_content is null-terminated.
void	read_heredoc_input(char **hd_content, int pipefd_read)
{
	char	buffer[1024];
	char	*temp;
	int		bytes_read;
	int		total_bytes;

	signal(SIGINT, handle_child_signal);
	total_bytes = 0;
	bytes_read = read(pipefd_read, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		temp = malloc(total_bytes + bytes_read + 1);
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
