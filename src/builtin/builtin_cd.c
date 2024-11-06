/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:57:06 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/06 10:54:30 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

void	print_cd_error(char *arg, char *message)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}

int	builtin_cd(char **args, char **env)
{
	char	*path;

	(void)env;
	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			print_cd_error(NULL, "HOME not set");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		print_cd_error(args[1], "No such file or directory");
		return (1);
	}
	return (0);
}
