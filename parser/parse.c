/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:04:18 by etien             #+#    #+#             */
/*   Updated: 2024/10/30 16:04:08 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This file contains the recursive descent parsing functions.
// Each function represents a rule of the command-line grammar and
// will generally call other parsing functions based on the tokens
// encountered next. Together, the functions will build up a parsing tree.
// The input into the functions are generally a double pointer to start of
// scan and a pointer to end of the input buffer. The ss double pointer is
// updated every time get_token or check_for_token is called.
// All of the functions will return the root node of the part of the tree
// it has built.
// The parsing will flow as follows:
// parse_line -> parse_cmd -> parse_pipe/parse_redir/parse_exec
// For complex commands, the tree hierarchy from root to leaf will be:
// PIPE - REDIR - EXEC

t_cmd	*parse_line
{
	t_cmd	*cmd;

	return (cmd);
}

t_cmd	*parse_cmd()
{
	t_cmd	*cmd;

	return (cmd);
}

// parse_pipe -> parse_exec/parse_pipe
// This function will parse pipelines (commands chained together with '|').
// It will set up a pipe node then call parse_exec to parse the left command.
// The right command will be parsed with a recursive call to itself in case
// there are more pipes to be parsed.
// If there are multiple pipes, the parsing tree is expanded downwards.
t_cmd	*parse_pipe(char **ss, char *es)
{
	t_cmd	*cmd;

	cmd = parse_exec(ss, es);
	if (check_for_token(ss, es, "|"))
	{
		get_token(ss, es, 0, 0);
		cmd = pipe_cmd(cmd, parse_pipe(ss,es));
	}
	return (cmd);
}

t_cmd	*parse_exec(char **ss, char *es)
{
	t_cmd	*cmd;

	return (cmd);
}

// independent function - no recursion or function calls
// This function will set up the REDIR nodes and apply the correct
// fd and mode based on the redirection symbol detected.
// An EXEC node is usually passed in as a parameter.
// Its pointer will be updated to the REDIR node and the original
// EXEC node will be connected as a child node to the REDIR node.
// Reusing the pointer removes the need to create a local variable
// and minimizes redundant pointers.
// Reminder: fd is set manually!
t_cmd	*parse_redir(t_cmd *cmd, char **ss, char *es)
{
	int	tok;

	if (tok == '<')
	else if (tok == '>')
	else if (tok == '+')


	return (cmd);
}
