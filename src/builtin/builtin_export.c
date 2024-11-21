/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:58:14 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/21 09:35:21 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

// TO-DO: when argument doesn't contain '=' it appears on env

/**
 * Print error message for export
 */
static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/**
 * Function to add a new variable to env
 *
 * 1. Get the number of variables in env
 * 2. Duplicate the new variable to env along with its value
 * 3. Add NULL terminator at the end
 */
static int	add_to_env(char **env, const char *new_var)
{
	int	i;

	i = get_env_size(env);
	env[i] = ft_strdup(new_var);
	if (!env[i])
		return (0);
	env[i + 1] = NULL;
	return (1);
}

/**
 * Function to update/add value of a variable
 *
 * 1. Get variable name length
 * 2. Copy variable name to var_name
 * 3. Check for if the variable name is valid
 * 4. Update value for variable if it already exists
 * 5. If variable is new, add variable to env
 */
static int	handle_equal(char **env, char *arg, char *equal_sign)
{
	char	var_name[PATH_MAX];
	int		name_len;

	name_len = equal_sign - arg;
	ft_strlcpy(var_name, arg, name_len + 1);
	if (!valid_var_name(var_name))
	{
		print_export_error(arg);
		return (1);
	}
	if (!update_env_value(env, var_name, equal_sign + 1))
		return (add_to_env(env, arg));
	return (0);
}

/**
 * Main builtin_export function
 *
 * 1. Check for arguments
 * 2. If no arguments, print env in alphabetical order
 * 3. If theres arguments, loop through the arguments.
 * 4. Check for '=' in the argument. If exists, call handle_equal
 * 5. If theres no '=', check for valid variable name
 * 6. Add valid variable to env
 */
int	builtin_export(char **args, char **env)
{
	int		i;
	char	*equal_sign;

	if (!args[1])
		return (print_sorted_env(env));
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign && handle_equal(env, args[i], equal_sign))
			return (1);
		else
		{
			if (!valid_var_name(args[i]))
			{
				print_export_error(args[i]);
				return (1);
			}
			if (!add_to_env(env, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
