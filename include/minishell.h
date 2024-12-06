/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:47:31 by etien             #+#    #+#             */
/*   Updated: 2024/12/06 14:06:18 by abinti-a         ###   ########.fr       */
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
# include <linux/limits.h>

// boolean data type
# include <stdbool.h>

// program header files
# include "builtin.h"
# include "expansion.h"
# include "heredoc.h"
# include "parser.h"
# include "utils.h"

// Error messages
# define EXEC_ERR "msh: command not found: "
# define SYNTAX_PIPE "minishell: syntax error near unexpected token `|'"
# define SYNTAX_QUOTES "minishell: syntax error: unclosed quotes"
# define SYNTAX_REDIR "minishell: syntax error near unexpected token \
`<' or '>' "

extern volatile sig_atomic_t g_signal_received;

// Struct to store env and exit status
typedef struct s_mshell
{
	char	**env;
	int		last_exit_status;
}			t_mshell;

// Error functions
bool		syntax_error(char *input);
void		print_error(char *err_msg, char *input, char *s);
void setup_signal_handling(void);

#endif
