/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:21 by etien             #+#    #+#             */
/*   Updated: 2024/11/13 15:29:37 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This file contains the constructor functions for the various nodes
// that will be used to construct the parsing tree.
// The general flow of each function is as follows:
// - malloc the node
// - call memset as an initialization measure to prevent undefined behaviour
// - fill in the fields in the node with parameters passed in to
//   the constructor function

// Constructor for PIPE node
// Other than type, all other node fields are extracted from
// function parameters.
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

// Constructor for EXEC node
// Only type is set as arrays will be filled up in the parse_exec function.
t_cmd	*exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

// Constructor for REDIR node
// Other than type, all other node fields are extracted from
// function parameters.
// cmd parameter renamed to subcmd to prevent naming confusion.
// When the function is called, a REDIR node is created.
// If the subcmd root node is also a REDIR node, we will traverse
// down the existing REDIR chain to slot the new REDIR node right
// above the EXEC node. This ensures that later redirections from
// the input overwrite previous ones.
t_cmd	*redir_cmd(char *file, char *efile, int redir_mode, t_cmd *subcmd)
{
	t_redir_cmd	*cmd;
	t_redir_cmd	*last_redir;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	if (redir_mode == INPUT)
	{
		cmd->mode = O_RDONLY;
		cmd->fd = 0;
	}
	else if (redir_mode == OUTPUT)
	{
		cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd = 1;
	}
	else if (redir_mode == APPEND)
	{
		cmd->mode = O_WRONLY | O_CREAT | O_APPEND;
		cmd->fd = 1;
	}
	cmd->file = ft_substr(file, 0, efile - file);
	if (subcmd->type == REDIR)
	{
		last_redir = (t_redir_cmd *)subcmd;
		while (last_redir->cmd->type == REDIR)
			last_redir = (t_redir_cmd *)last_redir->cmd;
		cmd->cmd = last_redir->cmd;
		last_redir->cmd = (t_cmd *)cmd;
		return (subcmd);
	}
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}
