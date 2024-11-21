/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:43:12 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/21 10:59:18 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

/**
 * Function to loop over the environment variables to print to output
 * Will only print variable that has a '=' at the end
 */
int	builtin_env(char **args, char **env)
{
	int		i;
	char	*equal_sign;

	(void)args;
	if (!env)
	{
		ft_putendl_fd("Error: No environment variables available", 2);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
			ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

/* int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	if (builtin_env(NULL, env) != 0)
	{
		write(2, "Error: builtin_env failed\n", 26);
		return (1);
	}
	return (0);
} */
