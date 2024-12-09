/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:04:18 by etien             #+#    #+#             */
/*   Updated: 2024/12/09 20:45:51 by etien            ###   ########.fr       */
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
t_cmd	*parse_cmd(char *s, t_mshell *shell)
{
	t_cmd	*cmd;
	char	*es;

	es = s + ft_strlen(s);
	cmd = parse_pipe(&s, es, shell);
	return (cmd);
}

// parse_pipe -> parse_exec/parse_pipe
// GRAMMAR: EXEC [PIPE]
// This function will parse pipelines (commands chained together with '|').
// It will set up a pipe node then call parse_exec to parse the left command.
// The right command will be parsed with a recursive call to itself in case
// there are more pipes to be parsed.
// If there are multiple pipes, the parsing tree is expanded downwards.
t_cmd	*parse_pipe(char **ss, char *es, t_mshell *shell)
{
	t_cmd	*cmd;

	cmd = parse_exec(ss, es, shell);
	if (check_for_token(ss, es, "|"))
	{
		get_token(ss, es, 0, 0);
		cmd = pipe_cmd(cmd, parse_pipe(ss, es, shell));
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
// Both argv and argv[i] are dynamically-allocated.
t_cmd	*parse_exec(char **ss, char *es, t_mshell *shell)
{
	t_cmd		*root;
	t_exec_cmd	*cmd;
	char		*st;
	char		*et;
	int			i;

	root = exec_cmd();
	cmd = (t_exec_cmd *)root;
	root = parse_redir(root, ss, es, shell);
	malloc_argv(*ss, cmd);
	i = 0;
	while (*ss < es && !check_for_token(ss, es, "|"))
	{
		get_token(ss, es, &st, &et);
		cmd->argv[i] = ft_substr(st, 0, et - st);
		i++;
		root = parse_redir(root, ss, es, shell);
	}
	cmd->argv[i] = 0;
	expand_argv(cmd->argv, shell);
	return (root);
}

// This function will dynamically allocate the argv array size in
// EXEC nodes. A local pointer is created to walk the string until
// either the string terminates or a pipe symbol is encountered, and
// the number of word and redirection tokens are counted. Since every
// redirection token will be accompanied by a word token, the array size
// must discount the word tokens that belong to redirections.
// An additional one space is allocated for the null terminator.
void	malloc_argv(char *s, t_exec_cmd *cmd)
{
	char	*s_local;
	int		tok;
	int		word_count;
	int		redir_count;

	s_local = s;
	tok = 0;
	word_count = 0;
	redir_count = 0;
	while (*s_local)
	{
		tok = get_token(&s_local, s_local + ft_strlen(s_local), NULL, NULL);
		if (tok == '|')
			break ;
		else if (tok == 'w')
			word_count++;
		else if (ft_strchr("<>+-", tok))
			redir_count++;
	}
	cmd->argv = malloc((word_count - redir_count + 1) * sizeof(char *));
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
t_cmd	*parse_redir(t_cmd *cmd, char **ss, char *es, t_mshell *shell)
{
	int			tok;
	t_tok_pos	*tok_pos;

	tok_pos = malloc(sizeof(*tok_pos));
	ft_memset(tok_pos, 0, sizeof(*tok_pos));
	while (check_for_token(ss, es, "<>"))
	{
		tok = get_token(ss, es, 0, 0);
		get_token(ss, es, &(tok_pos->st), &(tok_pos->et));
		if (tok == '<')
			cmd = redir_cmd(tok_pos, REDIR_INPUT, cmd, shell);
		else if (tok == '-')
			cmd = redir_cmd(tok_pos, REDIR_HEREDOC, cmd, shell);
		else if (tok == '>')
			cmd = redir_cmd(tok_pos, REDIR_OUTPUT, cmd, shell);
		else if (tok == '+')
			cmd = redir_cmd(tok_pos, REDIR_APPEND, cmd, shell);
	}
	free(tok_pos);
	return (cmd);
}
