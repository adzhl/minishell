/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:10:16 by etien             #+#    #+#             */
/*   Updated: 2024/12/18 17:31:30 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
