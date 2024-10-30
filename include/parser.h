/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:19:09 by etien             #+#    #+#             */
/*   Updated: 2024/10/30 16:51:18 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// The type of parsing tree node is given an integer representation.
# define EXEC 1
# define REDIR 2
# define PIPE 3

// Array size for the execcmd node.
# define MAX_ARGS 10

// Space, tab, carriage return, newline, verical tab
# define WHITESPACE " \t\r\n\v"
// Symbol tokens that have to be detected by the parser
# define SYMBOLS "|<>"

// Redirection modes
# define INPUT 1
# define OUTPUT 2
# define APPEND 3

// Struct declarations for parsing tree nodes
// General cmd struct to allow typecasting between different types of nodes.
typedef struct s_cmd
{
	int	type;
}	t_cmd;

// argv array will store pointers to the commands, command options and arguments
// e.g. echo -n "Hello", argv = ["echo", "-n", "Hello"]
// eargv array will store pointers to where the null terminator should go
// after each string
// e.g. "echo\0"
//			  ^ pointer
typedef struct s_exec_cmd
{
	int		type;
	char	*argv[MAX_ARGS];
	char	*eargv[MAX_ARGS];
}			t_exec_cmd;

// file and efile store pointers to the beginning and end of the filename.
// efile is included as a convenient way to null terminate the string.
// mode: O_WRONLY | O_RDONLY | O_CREATE | O_TRUNC | O_APPEND
// fd: STDOUT = 0; STDIN = 1;
// cmd stores the execcmd node that the redirection will be applied to.
// This implies that if there is redirection, it will always be the
// parent node to an execcmd node.
typedef struct s_redir_cmd
{
	int		type;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
	t_cmd	*cmd;
}	t_redir_cmd;

// Pipes will connect two processes.
// The left and right pointers will point to the two processes
// respectively that are connected by the pipe.
typedef struct s_pipe_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe_cmd;

// Constructor functions for parsing tree nodes
t_cmd	*exec_cmd(void);
t_cmd	*redir_cmd(char *file, char *efile, int redir_mode, t_cmd *subcmd);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);

// Token functions
int		get_token(char **ss, char *es, char **st, char **et);
void	detect_token(int *tok, char **s, char *es);
int		check_for_token(char **ss, char *es, char *toks);

// Parsing functions

// Parsing util functions
t_cmd	*null_terminate(t_cmd *cmd);

#endif
