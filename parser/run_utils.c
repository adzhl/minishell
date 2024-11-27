/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:10:16 by etien             #+#    #+#             */
/*   Updated: 2024/11/27 13:38:38 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will detect for pipe symbols in the input and either
// call run_cmd directly (if there are pipes) or fork a child process
// to run simple commands. run_cmd will fork child processes for PIPE
// nodes, but we will have to fork them manually if the input does not
// contain pipes. This is necessary so that control will be returned to
// the parent process after the child executes the command and terminates.
// It will prevent the program from exiting immediately.
void	run_cmd_control(char *input, t_cmd *ast, t_mshell *shell)
{
	bool	has_pipe;

	has_pipe = ft_strchr(input, '|');
	free(input);
	if (has_pipe)
		run_cmd(ast, shell);
	else
	{
		if (fork() == 0)
		{
			run_cmd(ast, shell);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
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
	*pcmd = (t_pipe_cmd *)cmd;
	*rcmd = (t_redir_cmd *)cmd;
	*ecmd = (t_exec_cmd *)cmd;
}
