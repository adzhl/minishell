/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:51:24 by etien             #+#    #+#             */
/*   Updated: 2024/12/12 13:07:57 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will walk the parsing tree and execute the commands.
// If the current node is an EXEC node, it will execute, otherwise
// the function will recursively call itself to continue descending
// down the parsing tree.
void	run_cmd(t_cmd *cmd, t_mshell *shell)
{
	t_pipe_cmd	*pcmd;
	t_redir_cmd	*rcmd;
	t_exec_cmd	*ecmd;

	cmd_typecasting(cmd, &pcmd, &rcmd, &ecmd);
	if (!cmd)
		exit(EXIT_FAILURE);
	if (cmd->type == PIPE)
		set_pipe(pcmd, shell);
	else if (cmd->type == EXEC)
		run_exec(shell, ecmd);
	else if (cmd->type == REDIR)
		set_redirection(rcmd, shell);
}

// This function will set up the pipes, fork two child processes and
// call run_cmd in each child process to continue descending down the
// left and right trees respectively.
// The parent process will wait for both children to terminate.
// Even though fork is called twice, only two child processes are created
// because each child will exit when run_cmd is called.
void	set_pipe(t_pipe_cmd *pcmd, t_mshell *shell)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_right;

	pipe(pipefd);
	pid_left = fork();
	if (pid_left == 0)
	{
		setup_child(0, pipefd[WRITE], pipefd);
		run_cmd(pcmd->left, shell);
		exit(EXIT_SUCCESS);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		setup_child(pipefd[READ], 0, pipefd);
		run_cmd(pcmd->right, shell);
		exit(EXIT_SUCCESS);
	}
	close_pipes(pipefd);
	waitpid(pid_right, &status_right, 0);
	handle_child_exit(status_right, shell);
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
		pipe_heredoc(rcmd);
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
