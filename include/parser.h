/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:19:09 by etien             #+#    #+#             */
/*   Updated: 2024/11/29 12:29:43 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Space, tab, carriage return, newline, verical tab
# define WHITESPACE " \t\r\n\v"

// Pipe ends
# define READ 0
# define WRITE 1

// Parsing tree node types
typedef enum node_type
{
	EXEC,
	REDIR,
	PIPE
}	t_node_type;

// Redirection modes for redir_cmd constructor function
typedef enum redir_mode
{
	REDIR_INPUT,
	REDIR_HEREDOC,
	REDIR_OUTPUT,
	REDIR_APPEND
}	t_redir_mode;

// Struct declarations for parsing tree nodes
// General cmd struct to allow typecasting between different types of nodes.
typedef struct s_cmd
{
	int	type;
}	t_cmd;

// Pipes will connect two processes.
// The left and right pointers will point to the two processes
// respectively that are connected by the pipe.
typedef struct s_pipe_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe_cmd;

// argv array will store pointers to the commands, command options and arguments
// e.g. echo -n "Hello", argv = ["echo", "-n", "Hello"]
typedef struct s_exec_cmd
{
	int		type;
	char	**argv;
}			t_exec_cmd;

// - mode: O_WRONLY | O_RDONLY | O_CREATE | O_TRUNC | O_APPEND
// - fd (the old fd to be redirected from): STDOUT = 0; STDIN = 1
// - file will store pointers to the filename.
// - cmd stores the EXEC node that the redirection will be applied to.
// This implies that if there is redirection, it will always be the
// parent node to an EXEC node.
typedef struct s_redir_cmd
{
	int		type;
	int		mode;
	int		fd;
	char	*file;
	char	*heredoc;
	t_cmd	*cmd;
}	t_redir_cmd;

// Token position struct used in redir_cmd to fit parameter count limit.
typedef struct s_tok_pos
{
	char	*st;
	char	*et;
}	t_tok_pos;

// Constructor functions for parsing tree nodes
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*exec_cmd(void);
t_cmd	*redir_cmd(t_tok_pos *tok_pos,
			int redir_mode, t_cmd *subcmd, t_mshell *shell);
void	init_redir(int redir_mode, t_redir_cmd *cmd);
void	insert_redir(t_cmd *subcmd, t_redir_cmd *cmd);

// Token functions
int		get_token(char **ss, char *es, char **st, char **et);
void	detect_token(int *tok, char **s, char *es);
void	redirection_token(int *tok, char **s);
void	word_token(int *tok, char **s, char *es);
bool	check_for_token(char **ss, char *es, char *toks);

// Parsing functions
t_cmd	*parse_cmd(char *s, t_mshell *shell);
t_cmd	*parse_pipe(char **ss, char *es, t_mshell *shell);
t_cmd	*parse_exec(char **ss, char *es, t_mshell *shell);
void	malloc_argv(char *s, t_exec_cmd *cmd);
t_cmd	*parse_redir(t_cmd *cmd, char **ss, char *es, t_mshell *shell);

// Run command functions
void	run_cmd(t_cmd *cmd, t_mshell *shell);
void	set_pipe(t_pipe_cmd *pcmd, t_mshell *shell);
void	set_redirection(t_redir_cmd *rcmd, t_mshell *shell);
void	open_fd(t_redir_cmd *rcmd);
void	pipe_heredoc(t_redir_cmd *rcmd);

// Run command util functions
void	run_cmd_control(char *input, t_cmd *ast, t_mshell *shell);
void	run_builtin(t_cmd *cmd, t_mshell *shell);
char	*get_standalone_cmd(t_cmd *ast);
void	close_pipes(int *pipefd);
void	cmd_typecasting(t_cmd *cmd,
			t_pipe_cmd **pcmd, t_redir_cmd **rcmd, t_exec_cmd **ecmd);

// Clean up functions
void	free_ast(t_cmd *cmd);
void	free_redir_data(t_redir_cmd *rcmd);
void	free_exec_data(t_exec_cmd *ecmd);

#endif
