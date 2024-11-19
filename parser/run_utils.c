/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:10:16 by etien             #+#    #+#             */
/*   Updated: 2024/11/19 11:37:07 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
