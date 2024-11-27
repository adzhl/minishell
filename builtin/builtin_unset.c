/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:04:01 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/27 13:05:32 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Shift the remaining variable after the one we removed to the left
 */
static void	remove_var(char **env, int index)
{
	while (env[index])
	{
		env[index] = env[index + 1];
		index++;
	}
}

/**
 * Print error when variable name is not valid
 */
static void	print_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/**
 * 1. Check if there are any arguments
 * 2. Iterate through argument and check for valid variable name
 * 3. Find index containing variable name in env
 * 4. If found, remove variable from env
 * 5. Return (0) if successful
 */
int	builtin_unset(char **args, t_mshell *shell)
{
	int	i;
	int	exit_status;
	int	var_index;

	exit_status = 0;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!valid_var_name(args[i]))
		{
			print_unset_error(args[i]);
			exit_status = 1;
		}
		else
		{
			var_index = find_var_name(shell->env, args[i]);
			if (var_index != -1)
				remove_var(shell->env, var_index);
		}
		i++;
	}
	return (exit_status);
}
