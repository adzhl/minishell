/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:25:00 by etien             #+#    #+#             */
/*   Updated: 2024/12/18 17:56:59 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function is tailored for redirections with standalone
// built-in commands. Since standalone built-ins are run in the
// parent process, the file descriptors have to be restored
// to their default states after the built-in is run.
void	set_builtin_redir(t_redir_cmd *rcmd, t_mshell *shell)
{
	int	in;
	int	out;

	in = dup(STDOUT_FILENO);
	out = dup(STDIN_FILENO);
	if (rcmd->file)
		open_fd(rcmd);
	else if (rcmd->heredoc)
		pipe_heredoc(rcmd);
	run_builtin(rcmd->cmd, shell);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(out);
	close(in);
}

// This function will set up the correct redirection depending
// on whether it is a file or a heredoc. In both cases, it will
// call run_cmd to continue descending down the parsing tree.
// The first if condition is to handle the edge case where
// "<< EOF" is not followed by any command. The function returns
// to prevent any redirection from taking place. Control can then
// be returned to the prompt without any input residues.
void	set_redirection(t_redir_cmd *rcmd, t_mshell *shell)
{
	if (!get_standalone_cmd((t_cmd *)rcmd))
		return ;
	if (rcmd->file)
		open_fd(rcmd);
	else if (rcmd->heredoc)
	{
		if (shell->abort_exec)
			return ;
		pipe_heredoc(rcmd);
	}
	run_cmd(rcmd->cmd, shell);
}

// This function handles opening file descriptors for the REDIR nodes.
// If the third parameter in open() is omitted, file permissions default to
// the shell's umask (typically 022, which results in 0644 permissions). The
// more generous 0666 permissions will allow us to open the newly-created file.
// In a sequence of REDIR nodes, later redirections overwrite earlier ones
// because dup2 continuously reconfigures STDIN or STDOUT as we traverse
// down the chain.
void	open_fd(t_redir_cmd *rcmd)
{
	int	redir_fd;

	redir_fd = open(rcmd->file, rcmd->mode, 0666);
	if (redir_fd < 0)
	{
		perror(rcmd->file);
		exit(EXIT_FAILURE);
	}
	dup2(redir_fd, rcmd->fd);
}

// This function will write the heredoc to a pipe so that it will
// have a file descriptor that can interact with the dup2 function.
// Since heredocs are typically temporary files, the heredoc string
// can be immediately freed after it has been written to the pipe for
// memory efficiency.
void	pipe_heredoc(t_redir_cmd *rcmd)
{
	int	pipefd[2];

	pipe(pipefd);
	write(pipefd[WRITE], rcmd->heredoc, ft_strlen(rcmd->heredoc));
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN_FILENO);
	close(pipefd[READ]);
	free(rcmd->heredoc);
	rcmd->heredoc = NULL;
}
