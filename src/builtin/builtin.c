/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:28:56 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/04 07:46:05 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

/**
 * Initialize built-in commands table
 * A library that stores a list of built-in commands
 */
t_builtin	*init_builtin(void)
{
	static t_builtin	builtins[] = {{"echo", builtin_echo}, {"cd", \
		builtin_cd}, {"pwd", builtin_pwd}, {"export", builtin_export}, \
		{"unset", builtin_unset}, {"env", builtin_env}, {"exit", \
		builtin_exit}, {NULL, NULL}};

	return (builtins);
}

/**
 * Check if cmd is a built-in
 */
int	is_builtin(char *cmd)
{
	t_builtin	*builtins;
	int			i;

	i = 0;
	builtins = init_builtin();
	while (builtins[i].name)
	{
		if (!ft_strcmp(cmd, builtins[i].name))
			return (1);
		i++;
	}
	return (0);
}

/**
 * Execute built-in commands
 */
int	execute_builtin(char *cmd, char **args, char **env)
{
	t_builtin	*builtins;
	int			i;

	i = 0;
	builtins = init_builtin();
	while (builtins[i].name)
	{
		if (!ft_strcmp(cmd, builtins[i].name))
			return (builtins[i].func(args, env));
		i++;
	}
	return (1);
}
