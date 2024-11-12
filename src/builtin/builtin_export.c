/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:58:14 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/12 11:49:10 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

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

int	builtin_export(char **args, char **env)
{
	int		i;
	char	*equal_sign;

	if (!args[1])
		return (print_sorted_env(env));
	i = 0;
	while (args[++i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign && handle_equal(env, args[i], equal_sign))
			return (1);
		else if (!equal_sign && !valid_var_name(args[i]))
		{
			print_export_error(args[i]);
			return (1);
		}
	}
	return (0);
}
