/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:19:09 by etien             #+#    #+#             */
/*   Updated: 2024/10/29 11:23:29 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Macros for fd opening modes
# include <fcntl.h>

// The type of parsing tree node is given an integer representation.
# define EXEC 1
# define REDIR 2
# define PIPE 3

// Array size for the execcmd node.
# define MAX_ARGS 10

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
typedef struct s_execcmd
{
	int		type;
	char	*argv[MAX_ARGS];
	char	*eargv[MAX_ARGS];
}			t_execcmd;

// file and efile store pointers to the beginning and end of the filename.
// efile is included as a convenient way to null terminate the string.
// mode: O_WRONLY | O_RDONLY | O_CREATE | O_TRUNC | O_APPEND
// fd: STDOUT = 0; STDIN = 1;
// cmd stores the execcmd node that the redirection will be applied to.
// This implies that if there is redirection, it will always be the
// parent node to an execcmd node.
typedef struct s_redircmd
{
	int		type;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
	t_cmd	*cmd;
}	t_redircmd;

// Pipes will connect two processes.
// The left and right pointers will point to the two processes
// respectively that are connected by the pipe.
typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

#endif
