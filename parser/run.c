/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:51:24 by etien             #+#    #+#             */
/*   Updated: 2024/11/07 11:37:54 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TO-DO: CREATE EXEC FUNCTION!!!

// This function will walk the parsing tree and execute the commands.
// If the current node is an EXEC node, it will execute, otherwise
// the function will recursively call itself to continue descending
// down the parsing tree.
void	run_cmd(t_cmd *cmd)
{
	t_exec_cmd	*ecmd;

	ecmd = NULL;
	if (!cmd)
		exit(EXIT_FAILURE);
	if (cmd->type == PIPE)
		set_pipes((t_pipe_cmd *)cmd);
	else if (cmd->type == EXEC)
	{
		ecmd = (t_exec_cmd *)ecmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		//exec(ecmd->argv[0], ecmd->argv);
		printf("execution happens here\n");
		ft_putstr_fd(EXEC_ERR, 2);
		ft_putendl_fd(ecmd->argv[0], 2);
	}
	else if (cmd->type == REDIR)
	{
		open_fd((t_redir_cmd *)cmd);
		run_cmd(((t_redir_cmd *)cmd)->cmd);
	}
	exit(EXIT_SUCCESS);
}

// This function will set up the pipes, fork two child processes and
// call run_cmd in each child process to continue descending down the
// left and right trees respectively.
// The parent process will wait for both children to terminate.
// Even though fork is called twice, only two child processes are created
// because each child will exit when run_cmd is called.
void	set_pipes(t_pipe_cmd	*pcmd)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		perror(PIPE_ERR);
	if (fork_and_check() == 0)
	{
		dup2(pipefd[WRITE], STDOUT_FILENO);
		close_pipes(pipefd);
		run_cmd(pcmd->left);
	}
	if (fork_and_check() == 0)
	{
		dup2(pipefd[READ], STDIN_FILENO);
		close_pipes(pipefd);
		run_cmd(pcmd->right);
	}
	close_pipes(pipefd);
	wait(NULL);
	wait(NULL);
}

// This is a simple helper function to close both ends of a pipe.
void	close_pipes(int *pipefd)
{
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}

// This is a wrapper for the fork function.
// It will throw an error if the fork fails. Otherwise, it
// will return the child process pid.
int	fork_and_check(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror(FORK_ERR);
	return (pid);
}

// This function handles opening file descriptors for the REDIR nodes.
// If the third parameter in open() is omitted, file permissions default to
// the shell's umask (typically 022, which results in 0644 permissions).
// In a sequence of REDIR nodes, later redirections overwrite earlier ones
// because dup2 continuously reconfigures STDIN or STDOUT as we traverse
// down the chain.
void	open_fd(t_redir_cmd *rcmd)
{
	int	fd;

	fd = open(rcmd->file, rcmd->mode);
	if (fd < 0)
	{
		ft_putstr_fd(FILE_OPEN_ERR, 2);
		ft_putendl_fd(rcmd->file, 2);
		exit(1);
	}
	dup2(fd, rcmd->fd);
}
