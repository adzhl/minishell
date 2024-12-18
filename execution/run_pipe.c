/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:23:30 by etien             #+#    #+#             */
/*   Updated: 2024/12/18 17:42:00 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int		status_left;

	pipe(pipefd);
	pid_left = fork();
	if (pid_left == 0)
	{
		setup_child(0, pipefd[WRITE], pipefd);
		run_cmd(pcmd->left, shell);
		exit(shell->last_exit_status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		setup_child(pipefd[READ], 0, pipefd);
		run_cmd(pcmd->right, shell);
		exit(shell->last_exit_status);
	}
	close_pipes(pipefd);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	handle_child_exit(status_right, shell);
}

// This function will duplicate the pipe file descriptors to the
// standard file descriptors.
void	setup_child(int inputfd, int outputfd, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (inputfd)
		dup2(inputfd, STDIN_FILENO);
	if (outputfd)
		dup2(outputfd, STDOUT_FILENO);
	close_pipes(pipefd);
}

// This is a helper function to close both ends of a pipe.
void	close_pipes(int *pipefd)
{
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}
