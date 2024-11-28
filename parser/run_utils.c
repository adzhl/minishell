/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:10:16 by etien             #+#    #+#             */
/*   Updated: 2024/11/28 18:53:15 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function checks for pipe symbols in the input to differentiate
// between standalone commands and piped commands. For piped commands,
// the run_cmd function can be called directly, as it handles child process
// creation in its PIPE nodes. However, for standalone commands, built-in
// functions must be executed in the parent process to ensure that changes
// to the environment variables (ENV) persist across subsequent commands.
// If the standalone command is not a built-in, a child process must be forked
// manually to execute it. This prevents the execve call from terminating
// the parent process. The goal is to ensure that control returns to the
// shell prompt after execution, avoiding an immediate program exit.
void	run_cmd_control(char *input, t_cmd *ast, t_mshell *shell)
{
	bool	has_pipe;

	has_pipe = ft_strchr(input, '|');
	free(input);
	if (!has_pipe && !is_builtin(get_standalone_cmd(ast)))
	{
		if (fork() == 0)
		{
			run_cmd(ast, shell);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
	else if (!has_pipe && is_builtin(get_standalone_cmd(ast)))
		run_builtin(ast, shell);
	else
		run_cmd(ast, shell);
}

// This function is similar to the run_cmd function, except it
// is only run when there is a standalone built-in command.
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
		set_redirection(rcmd, shell);
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
void	cmd_typecasting(t_cmd *cmd,
	t_pipe_cmd **pcmd, t_redir_cmd **rcmd, t_exec_cmd **ecmd)
{
	if (pcmd)
		*pcmd = (t_pipe_cmd *)cmd;
	if (rcmd)
		*rcmd = (t_redir_cmd *)cmd;
	if (ecmd)
		*ecmd = (t_exec_cmd *)cmd;
}
