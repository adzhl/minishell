/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:01:18 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/11 08:15:59 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	update_env_value(char **env, const char *name, const char *value)
{
	int		i;
	int		len;
	char	*temp;
	char	*new_var;

	len = 0;
	while (name[len])
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			temp = ft_strjoin(name, "=");
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
