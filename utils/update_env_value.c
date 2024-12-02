/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:01:18 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/02 09:34:20 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Update an environment variable by overwriting the value with a new one
 */
int	update_env_value(char **env, const char *name, const char *value)
{
	int		i;
	int		len;
	char	*temp;
	char	*new_var;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			temp = ft_strjoin(name, "=");
			if (!temp)
				return (0);
			new_var = ft_strjoin(temp, value);
			free(temp);
			if (!new_var)
				return (0);
			free(env[i]);
			env[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_mshell shell;

// 	shell.env = copy_env(envp);
// 	printf("Env Before update\n");
// 	builtin_env(NULL, &shell);
// 	printf("\n");
// 	update_env_value(shell.env, "testing", "new value");
// 	printf("Env After:\n");
// 	builtin_env(NULL, &shell);
// 	return (0);
// }
