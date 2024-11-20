/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:04:18 by etien             #+#    #+#             */
/*   Updated: 2024/11/20 10:56:59 by etien            ###   ########.fr       */
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
// to start building the parsing tree.
// The input buffer is passed in as a parameter to the function.
t_cmd	*parse_cmd(char *s)
{
	t_cmd	*cmd;
	char	*es;

	es = s + ft_strlen(s);
	cmd = parse_pipe(&s, es);
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
// This function will construct the EXEC node in between parse_redir calls.
// The function will have two pointers, root and cmd.
// cmd is used to populate the EXEC node while root node keeps track of
// the root of the constructed tree even when multiple parse_redir calls wrap
// more REDIR nodes around the EXEC node.
// The while loop only checks for '|' because the earlier call to
// parse_redir already checked for '<' and '>'.
// The call to parse_redir at the end of each while loop run allows redirections
// to be interspersed between command arguments,
// e.g. command arg1 > output.txt arg2 < input.txt
// argv is allocated on the stack but argv[i] are dynamically-allocated.
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
	while (*ss < es && !check_for_token(ss, es, "|"))
	{
		get_token(ss, es, &st, &et);
		if (i < MAX_ARGS)
			cmd->argv[i] = ft_substr(st, 0, et - st);
		i++;
		root = parse_redir(root, ss, es);
	}
	if (i > MAX_ARGS)
	{
		i = MAX_ARGS;
		ft_putendl_fd(TOO_MANY_ARGS, 2);
	}
	cmd->argv[i] = 0;
	return (root);
}

// independent function - no recursion or function calls
// GRAMMAR: [REDIR] [REDIR]
// This function will set up the REDIR nodes and apply the correct
// fd and mode based on the redirection symbol detected.
// Before any REDIR nodes are created, the function checks that the
// redirection token is followed by a word token.
// The word token will either be the file name or the EOF for the heredoc.
// If the word token is absent, an error is thrown and the AST will be freed.
// The while loop allows this function to parse multiple redirection
// operators in a row, e.g. command > file1 < file2 >> file3.
// Since cmd is reused, if there are multiple redirections, the REDIR
// constructor will incorporate the existing cmd tree and extend it.
t_cmd	*parse_redir(t_cmd *cmd, char **ss, char *es)
{
	int		tok;
	char	*st;
	char	*et;

	while (check_for_token(ss, es, "<>"))
	{
		tok = get_token(ss, es, 0, 0);
		get_token(ss, es, &st, &et);
		if (tok == '<')
			cmd = redir_cmd(st, et, R_INPUT, cmd);
		else if (tok == '-')
			cmd = redir_cmd(st, et, R_HEREDOC, cmd);
		else if (tok == '>')
			cmd = redir_cmd(st, et, R_OUTPUT, cmd);
		else if (tok == '+')
			cmd = redir_cmd(st, et, R_APPEND, cmd);
	}
	return (cmd);
}
