/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:30:00 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/09 22:38:15 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(char *cmd, t_mshell *shell)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*append_cmd;
	int		i;

	path_var = get_env_value(shell->env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	i = 0;
	while (paths[i])
	{
		append_cmd = ft_strjoin(paths[i], "/");
		if (!append_cmd)
			return (free_array(paths), NULL);
		full_path = ft_strjoin(append_cmd, cmd);
		free(append_cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_array(paths), full_path);
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}
