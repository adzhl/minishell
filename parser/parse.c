/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:04:18 by etien             #+#    #+#             */
/*   Updated: 2024/11/07 11:35:15 by etien            ###   ########.fr       */
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
// parse_cmd -> parse_pipe -> parse_exec/parse_redir/parse_pipe
// For complex commands, the tree hierarchy from root to leaf will be:
// PIPE - REDIR - EXEC

// This function is the entry point for parsing and will call parse_pipe
// to start building the parsing tree. After the recursive calls are complete,
// it will call null_terminate to cap off the strings in the tree.
// The input buffer is passed in as a parameter to the function.
t_cmd	*parse_cmd(char *s)
{
	t_cmd	*cmd;
	char	*es;

	es = s + ft_strlen(s);
	cmd = parse_pipe(&s, es);
	null_terminate(cmd);
	return (cmd);
}

// parse_pipe -> parse_exec/parse_pipe
// GRAMMAR: EXEC [PIPE]
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
		cmd = pipe_cmd(cmd, parse_pipe(ss, es));
	}
	return (cmd);
}

// parse_exec -> parse_redir
// GRAMMAR: [REDIR] EXEC [REDIR]
// This function will set up the EXEC node and sandwich it
// between parse_redir calls.
// The function will have two pointers, root and cmd.
// cmd is used to populate the EXEC node while root node keeps track of
// the root of the constructed tree even when multiple parse_redir calls wrap
// more REDIR nodes around the EXEC node.
// The while loop only checks for '|' and '\0' because the earlier call to
// parse_redir already checked for '<' and '>'.
// The call to parse_redir at the end of each while loop run allows redirections
// to be interspersed between command arguments,
// e.g. command arg1 > output.txt arg2 < input.txt

t_cmd	*parse_exec(char **ss, char *es)
{
	t_cmd		*root;
	t_exec_cmd	*cmd;
	char		*st;
	char		*et;
	int			i;

	root = exec_cmd();
	cmd = (t_exec_cmd *)root;
	root = parse_redir(root, ss, es);
	i = 0;
	while (!check_for_token(ss, es, "|\0"))
	{
		get_token(ss, es, &st, &et);
		cmd->argv[i] = st;
		cmd->eargv[i] = et;
		i++;
		if (i >= MAX_ARGS)
			perror(EXCEEDED_MAX_ARGS);
		root = parse_redir(root, ss, es);
	}
	cmd->argv[i] = 0;
	cmd->eargv[i] = 0;
	return (root);
}

// independent function - no recursion or function calls
// GRAMMAR: [REDIR] [REDIR]
// This function will set up the REDIR nodes and apply the correct
// fd and mode based on the redirection symbol detected.
// The while loop allows this function to parse multiple redirection
// operators in a row, e.g. command > file1 < file2 >> file3.
// Since cmd is reused, if there are multiple redirections, the REDIR
// constructor will incorporate the existing cmd tree and extend it.
// Later redirections will become parent nodes of the previously built tree.
// An EXEC node is usually passed in as a parameter.
// Its pointer will be updated to the REDIR node and the original
// EXEC node will be connected as a child node to the REDIR node.
// Reusing the pointer removes the need to create a local variable
// and minimizes redundant pointers.
t_cmd	*parse_redir(t_cmd *cmd, char **ss, char *es)
{
	int		tok;
	char	*st;
	char	*et;

	while (check_for_token(ss, es, "<>"))
	{
		tok = get_token(ss, es, 0, 0);
		if (get_token(ss, es, &st, &et) != 'w')
			perror(NO_FILE);
		if (tok == '<')
			cmd = redir_cmd(st, et, INPUT, cmd);
		else if (tok == '>')
			cmd = redir_cmd(st, et, OUTPUT, cmd);
		else if (tok == '+')
			cmd = redir_cmd(st, et, APPEND, cmd);
	}
	return (cmd);
}

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
void	null_terminate(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
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
}
