/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:47:31 by etien             #+#    #+#             */
/*   Updated: 2024/11/27 08:55:22 by abinti-a         ###   ########.fr       */
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

// boolean data type
# include <stdbool.h>

// program header files
# include "parser.h"
# include "heredoc.h"
# include "expansion.h"
# include "builtin.h"
# include "utils.h"

// Error messages
# define EXEC_ERR ": command not found"
# define SYNTAX_PIPE "minishell: syntax error near unexpected token `|'"
# define SYNTAX_QUOTES "minishell: syntax error: unclosed quotes"
# define SYNTAX_REDIR "minishell: syntax error near unexpected token \
`<' or '>' "

// Error functions
bool	syntax_error(char *input);
void	print_error(char *err_msg, char *input, char *s);

#endif
