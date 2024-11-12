/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:57:06 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/11 09:21:52 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

/**
 * Error printing for cd command
 */
static void	print_cd_error(char *arg, char *message)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}

/**
 * Handle cd without any arguments by redirecting to HOME
 */
static int	handle_no_args(char **env, char **path)
{
	*path = get_env_value(env, "HOME");
	if (!*path)
	{
		print_cd_error(NULL, "HOME not set");
		return (1);
	}
	return (0);
}

/**
 * Update env value when changing directories
 */
static int	update_pwd(char **env, char *curr_dir, char *new_dir)
{
	if (!getcwd(new_dir, PATH_MAX))
	{
		print_cd_error(NULL, "getcwd failed");
		return (1);
	}
	update_env_value(env, "OLDPWD", curr_dir);
	update_env_value(env, "PWD", new_dir);
	return (0);
}

/**
 * 1. Check for an argument
 * 2. If no argument, change to HOME env
 * 3. If there is an argument, use chdir to change to the specified path
 * 4. If path does not exist, return an error.
 */
int	builtin_cd(char **args, char **env)
{
	char	*path;
	char	curr_dir[PATH_MAX];
	char	new_dir[PATH_MAX];

	(void)args;
	if (!args[1] && handle_no_args(env, &path))
		return (1);
	else if (args[1])
		path = args[1];
	if (!getcwd(curr_dir, PATH_MAX))
	{
		print_cd_error(NULL, "getcwd failed");
		return (1);
	}
	if (chdir(path) == -1)
	{
		print_cd_error(args[1], "No such file or directory");
		return (1);
	}
	return (update_pwd(env, curr_dir, new_dir));
}