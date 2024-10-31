/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:51:24 by etien             #+#    #+#             */
/*   Updated: 2024/10/31 12:49:43 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will walk the parsing tree and execute the commands.
// If the current node is an EXEC node, it will execute, otherwise
// the function will recursively call itself to continue descending
// down the parsing tree.
void run_cmd(t_cmd *cmd)
{
	t_pipe_cmd	*pcmd;
	t_exec_cmd	*ecmd;
	t_redir_cmd	*rcmd;

	if (!cmd)
		exit(EXIT_FAILURE);
	if (cmd->type == PIPE)
	{
		pcmd = (t_pipe_cmd *)cmd;
		set_pipes(pcmd);
	}
	else if (cmd->type == EXEC)
	{
		ecmd = (t_exec_cmd *)cmd;
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redir_cmd *)cmd;

	}
	exit(EXIT_SUCCESS);
}

// Even though fork is called twice, only two child processes are created
// because each child will exit when run_cmd is called.
void set_pipes(t_pipe_cmd	*pcmd)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		perror(PIPE_ERR);
	if (fork_and_check == 0)
	{
		close_pipes(pipefd);
		run_cmd(pcmd->left);
	}
	if (fork_and_check == 0)
	{
		close_pipes(pipefd);
		run_cmd(pcmd->left);
	}
	close_pipes(pipefd);
	wait(NULL);
	wait(NULL);
}

// This is a simple helper function to close both ends of a pipe.
void close_pipes(int *pipefd)
{
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}

// This is just a wrapper function for the fork function.
// It will throw an error if the fork fails. Otherwise, it
// will return the child process pid.
int fork_and_check(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror(FORK_ERR);
	return (pid);
}
