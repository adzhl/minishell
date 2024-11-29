/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:21 by etien             #+#    #+#             */
/*   Updated: 2024/11/29 12:25:07 by etien            ###   ########.fr       */
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
t_cmd	*exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	cmd->argv = NULL;
	return ((t_cmd *)cmd);
}

// Constructor for REDIR node
// Other than type, all other node fields are extracted/inferred from
// function parameters.
// File and heredoc fields are mutually exclusive, so file remains NULL for
// heredocs, and heredoc remains NULL for file-based redirections.
// Heredoc fd and mode are set to -1 to avoid confusion with valid values.
t_cmd	*redir_cmd(t_tok_pos *tok_pos,
			int redir_mode, t_cmd *subcmd, t_mshell *shell)
{
	t_redir_cmd	*cmd;
	char		*eof;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	init_redir(redir_mode, cmd);
	if (redir_mode != REDIR_HEREDOC)
		cmd->file = ft_substr(tok_pos->st, 0, tok_pos->et - tok_pos->st);
	else
	{
		cmd->mode = -1;
		cmd->fd = -1;
		eof = ft_substr(tok_pos->st, 0, tok_pos->et - tok_pos->st);
		cmd->heredoc = handle_heredoc(&eof, shell);
		free(eof);
	}
	if (subcmd->type == REDIR)
		return (insert_redir(subcmd, cmd), subcmd);
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

// This function initializes the file descriptors and file
// opening mode for redirections that involve files.
void	init_redir(int redir_mode, t_redir_cmd *cmd)
{
	if (redir_mode == REDIR_INPUT)
	{
		cmd->mode = O_RDONLY;
		cmd->fd = 0;
	}
	else if (redir_mode == REDIR_OUTPUT)
	{
		cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd = 1;
	}
	else if (redir_mode == REDIR_APPEND)
	{
		cmd->mode = O_WRONLY | O_CREAT | O_APPEND;
		cmd->fd = 1;
	}
}

// This function traverses down any existing REDIR chain to insert
// the new REDIR node above the EXEC node. This ensures that later
// redirections in the input always overwrite previous ones.
void	insert_redir(t_cmd *subcmd, t_redir_cmd *cmd)
{
	t_redir_cmd	*last_redir;

	last_redir = (t_redir_cmd *)subcmd;
	while (last_redir->cmd->type == REDIR)
		last_redir = (t_redir_cmd *)last_redir->cmd;
	cmd->cmd = last_redir->cmd;
	last_redir->cmd = (t_cmd *)cmd;
}
