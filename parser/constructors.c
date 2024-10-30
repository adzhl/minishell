/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:21 by etien             #+#    #+#             */
/*   Updated: 2024/10/30 12:47:26 by etien            ###   ########.fr       */
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
// Other than type and fd, all other node fields are extracted from
// function parameters.
// fd is set to -1 by default and will be manually updated when the
// redircmd node is initialized to keep within 4 function parameters.
// cmd parameter renamed to subcmd to prevent naming confusion.
t_cmd	*redir_cmd(char *file, char *efile, int mode, t_cmd *subcmd)
{
	t_redir_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = -1;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

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
