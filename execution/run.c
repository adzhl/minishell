/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:51:24 by etien             #+#    #+#             */
/*   Updated: 2024/12/18 17:32:49 by etien            ###   ########.fr       */
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
	else if (cmd->type == REDIR)
		set_builtin_redir(rcmd, shell);
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
}

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
	else if (cmd->type == REDIR)
		set_redirection(rcmd, shell);
	else if (cmd->type == EXEC)
		run_exec(shell, ecmd);
}
