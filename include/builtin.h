/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:09:39 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/11 09:43:39 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_mshell	t_mshell;

/**
 * Built-in command function pointer type
 * Returns: Exit status of the command (0 for success, other for failure)
 */
typedef int				(*t_builtin_func)(char **args, t_mshell *shell);

/**
 * name = cmd name
 * func = pointer to the function that implements the cmd
 */
typedef struct s_builtin
{
	char				*name;
	t_builtin_func		func;
}						t_builtin;

// Built-in functions
int						builtin_echo(char **args, t_mshell *shell);
int						builtin_cd(char **args, t_mshell *shell);
int						builtin_pwd(char **args, t_mshell *shell);
int						builtin_export(char **args, t_mshell *shell);
int						builtin_unset(char **args, t_mshell *shell);
int						builtin_env(char **args, t_mshell *shell);
int						builtin_exit(char **args, t_mshell *shell);

// Built-in utils
t_builtin				*init_builtins(void);
int						is_builtin(char *cmd);
int						execute_builtin(char *cmd, char **args,
							t_mshell *shell);

#endif
