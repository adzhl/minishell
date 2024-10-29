/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:21 by etien             #+#    #+#             */
/*   Updated: 2024/10/29 17:15:12 by etien            ###   ########.fr       */
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

// Constructor for execcmd node
// Only type is set as arrays will be filled up in the parseexec function.
t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

// Constructor for redircmd node
// Other than type and fd, all other node fields are extracted from
// function parameters.
// fd is set to -1 by default and will be manually updated when the
// redircmd node is initialized to keep within 4 function parameters.
// cmd parameter renamed to subcmd to prevent naming confusion.
t_cmd	*redircmd(char *file, char *efile, int mode, t_cmd *subcmd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(t_redircmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = -1;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

// Constructor for pipecmd node
// Other than type, all other node fields are extracted from
// function parameters.
t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(t_pipecmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
