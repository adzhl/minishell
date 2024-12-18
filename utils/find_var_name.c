/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:42:04 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/04 18:57:37 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Find the index of the environment variable needed to be removed
 */
int	find_var_name(char **env, const char *name)
{
	int	i;
	int	name_len;

	name_len = (int)ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && \
		(env[i][name_len] == '=' || env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
