/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:47:31 by etien             #+#    #+#             */
/*   Updated: 2024/11/19 11:40:48 by etien            ###   ########.fr       */
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

// Error messages
# define EXCEEDED_MAX_ARGS "Command arguments count has exceeded MAX_ARGS."
# define FILE_OPEN_ERR "Error opening file: "

# define EXEC_ERR ": command not found"
# define SYNTAX_PIPE "minishell: syntax error near unexpected token `|'"
# define SYNTAX_QUOTES "minishell: syntax error: unclosed quotes"
# define SYNTAX_REDIR "minishell: syntax error near unexpected token \
`<' or '>' "

// Main util functions
void	run_cmd_control(char *input, t_cmd *ast);

// Error functions
bool	syntax_error(char *input);
void	print_error(char *err_msg, char *input, char *s);

#endif
