/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:10:16 by etien             #+#    #+#             */
/*   Updated: 2024/12/18 16:54:59 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function checks for pipe symbols in the input to identify
// standalone built-in commands. Standalone built-in commands must be
// executed in the parent process to ensure that changes to the environment
// variables (ENV) persist across subsequent commands. For all other types
// of commands, a child process must be forked manually before run_cmd is
// called. This prevents the execve call from terminating the parent process.
// The goal is to ensure that control returns to the shell prompt after
// execution, avoiding an immediate program exit.
void	run_cmd_control(char *input, t_cmd *ast, t_mshell *shell)
{
	bool	has_pipe;
	int		status;
	pid_t	pid;

	has_pipe = ft_strchr(input, '|');
	free(input);
	if (!has_pipe && is_builtin(get_standalone_cmd(ast)))
		run_builtin(ast, shell);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			run_cmd(ast, shell);
			exit(shell->last_exit_status);
		}
		signal(SIGINT, handle_child_signal);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_signal);
		handle_child_exit(status, shell);
	}
}

// This function is similar to the run_cmd function, except it
// is only run when there is a standalone built-in command.
// Standalone commands do not have pipes so PIPE nodes are
// omitted in the if-else checks.
void	run_builtin(t_cmd *cmd, t_mshell *shell)
{
	t_redir_cmd	*rcmd;
	t_exec_cmd	*ecmd;

	cmd_typecasting(cmd, NULL, &rcmd, &ecmd);
	if (!cmd)
		return ;
	else if (cmd->type == EXEC)
	{
		if (ecmd->argv[0] == 0)
			return ;
		if (is_builtin(ecmd->argv[0]))
		{
			if (execute_builtin(ecmd->argv[0], ecmd->argv, shell) != 0)
				return ;
		}
	}
	else if (cmd->type == REDIR)
		set_builtin_redir(rcmd, shell);
}

// This function will fetch the name of the standalone command.
char	*get_standalone_cmd(t_cmd *ast)
{
	t_cmd	*current_node;

	current_node = ast;
	while (current_node->type == REDIR)
		current_node = ((t_redir_cmd *)current_node)->cmd;
	if (current_node->type == EXEC)
		return (((t_exec_cmd *)current_node)->argv[0]);
	return (NULL);
}

// This is a helper function to close both ends of a pipe.
void	close_pipes(int *pipefd)
{
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}

// This is a helper function for parsing tree node typecasting.
void	cmd_typecasting(t_cmd *cmd, t_pipe_cmd **pcmd, t_redir_cmd **rcmd,
		t_exec_cmd **ecmd)
{
	if (pcmd)
		*pcmd = (t_pipe_cmd *)cmd;
	if (rcmd)
		*rcmd = (t_redir_cmd *)cmd;
	if (ecmd)
		*ecmd = (t_exec_cmd *)cmd;
}
