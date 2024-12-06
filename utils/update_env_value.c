/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:01:18 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/06 10:28:17 by abinti-a         ###   ########.fr       */
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
		if (ft_strncmp(env[i], name, len) == 0 && (env[i][len] == '='
				|| env[i][len] == '\0'))
		{
			temp = ft_strjoin(name, "=");
			if (!temp)
				return (1);
			new_var = ft_strjoin(temp, value);
			free(temp);
			if (!new_var)
				return (1);
			free(env[i]);
			env[i] = new_var;
			return (0);
		}
		i++;
	}
	return (1);
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
// 	int result = update_env_value(shell.env, "testing", "new value");
// 	printf("Env After:\n");
// 	builtin_env(NULL, &shell);
// 	printf("Exit status: %d\n", result);
// 	return (0);
// }

// builtin/builtin_env.c utils/update_env_value.c utils/copy_env.c libft/libft.a
