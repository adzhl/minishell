/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:04:21 by etien             #+#    #+#             */
/*   Updated: 2024/10/30 16:03:48 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will walk the parsing tree and null-terminate
// the strings that have been extracted from the input buffer:
// 	1) argv array elements in EXEC nodes
// 	2) filenames in REDIR nodes
// eargv and efile are pointers to where the null terminator should
// go within a string, and are therefore set to 0 (NULL).
// If a leaf node (usually EXEC) is not reached yet, the function is called
// recursively to continue descending down the tree.
// Typecasting is important here to access the specific fields of different
// types of nodes.
// Aside from being a safety measure, the null pointer check doubles as the base
// case so that recursive calls stop at the end of each branch in the tree/
// at NULL nodes.
t_cmd	*null_terminate(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (NULL);
	if (cmd->type == EXEC)
	{
		i = -1;
		while (((t_exec_cmd *)cmd)->argv[++i])
			*(((t_exec_cmd *)cmd)->eargv[i]) = 0;
	}
	else if (cmd->type == REDIR)
	{
		null_terminate(((t_redir_cmd *)cmd)->cmd);
		*(((t_redir_cmd *)cmd)->efile) = 0;
	}
	else if (cmd->type == PIPE)
	{
		null_terminate(((t_pipe_cmd *)cmd)->left);
		null_terminate(((t_pipe_cmd *)cmd)->right);
	}
	return (cmd);
}
