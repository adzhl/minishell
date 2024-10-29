/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:09:39 by abinti-a          #+#    #+#             */
/*   Updated: 2024/10/29 14:00:23 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/ft_printf/includes/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"

/**
 * Built-in command function pointer type
 * Returns: Exit status of the command (0 for success, other for failure)
 */
typedef int (*t_builtin_func)(char **args, char **env);

/**
 * name = cmd name
 * func = pointer to the function that implements the cmd
 */
typedef struct  s_builtin
{
    char *name;
    t_builtin_func func;
}               t_builtin;

//Global built-ins table
extern t_builtin g_builtins[];

//Built-in functions
int builtin_echo(char **args, char **env);
int builtin_cd(char **args, char **env);
int builtin_pwd(char **args, char **env);
int builtin_export(char **args, char **env);
int builtin_unset(char **args, char **env);
int builtin_env(char **args, char **env);
int builtin_exit(char **args, char **env);

//Built-in utils
//t_builtin *init_builtins(void);
int is_builtin(char *cmd);
int execute_builtin(char *cmd, char **args, char **env);

#endif 