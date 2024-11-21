/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:01:00 by etien             #+#    #+#             */
/*   Updated: 2024/11/21 09:20:17 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This clean-up function will free the abstract syntax tree.
// It will traverse down the tree recursively and free children nodes
// first before freeing the parent nodes.
void	free_ast(t_cmd *cmd)
{
	t_pipe_cmd	*pcmd;
	t_redir_cmd	*rcmd;
	t_exec_cmd	*ecmd;

	cmd_typecasting(cmd, &pcmd, &rcmd, &ecmd);
	if (!cmd)
		return ;
	if (cmd->type == PIPE)
	{
		free_ast(pcmd->left);
		free_ast(pcmd->right);
		free(pcmd);
	}
	else if (cmd->type == REDIR)
	{
		free_ast(rcmd->cmd);
		free_redir_data(rcmd);
		free(rcmd);
	}
	else if (cmd->type == EXEC)
	{
		free_exec_data(ecmd);
		free(ecmd);
	}
}

// A helper function to free the REDIR fields.
void	free_redir_data(t_redir_cmd *rcmd)
{
	if (rcmd->file)
		free(rcmd->file);
	if (rcmd->heredoc)
		free(rcmd->heredoc);
}

// A helper function to free the EXEC fields.
void	free_exec_data(t_exec_cmd *ecmd)
{
	int	i;

	i = -1;
	while (ecmd->argv[++i])
		free(ecmd->argv[i]);
	free(ecmd->argv);
}
