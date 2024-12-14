/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:47:31 by etien             #+#    #+#             */
/*   Updated: 2024/12/14 11:14:17 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libft library
# include "../libft/libft/libft.h"

// readline library
// readline
# include <readline/readline.h>
// add_history
# include <readline/history.h>

// printf, perror
# include <stdio.h>
// malloc, free, exit, getenv
# include <stdlib.h>
// fork, execve, chdir, getcwd, access, pipe, dup, dup2
# include <unistd.h>
// wait, waitpid
# include <sys/wait.h>
// pid_t data type
# include <sys/types.h>
// signal, sigaction, kill, sigemptyset
# include <signal.h>
// open, close
# include <fcntl.h>
// PATH_MAX
# include <limits.h>

// boolean data type
# include <stdbool.h>

// program header files
# include "builtin.h"
# include "execution.h"
# include "expansion.h"
# include "heredoc.h"
# include "parser.h"
# include "utils.h"

// Error messages
# define EXEC_ERR "msh: command not found: "
# define SYNTAX_PIPE "msh: syntax error near unexpected token `|'"
# define SYNTAX_QUOTES "msh: syntax error: unclosed quotes"
# define SYNTAX_REDIR "msh: syntax error near unexpected token `<' or '>'"
# define HEREDOC_ERR "msh: warning: here-document delimited by end-of-file"

extern volatile sig_atomic_t	g_signal_received;

// Struct to store env and exit status
typedef struct s_mshell
{
	char						**env;
	int							last_exit_status;
	bool						abort_exec;
}								t_mshell;

// Main functions
void							init_shell(t_mshell *shell, char **envp);
void							handle_signal_main(t_mshell *shell);
void							exit_shell(void);

// Error functions
bool							syntax_error(char *input);
void							print_error(char *err_msg, char *input,
									char *s);

// Signal functions
void							setup_signal_handling(void);
void							handle_signal(int signum);
void							handle_signal_heredoc(t_mshell *shell,
									int status);
void							handle_child_exit(int status, t_mshell *shell);
void							handle_child_signal(int signum);

#endif
