/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:30:00 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/16 16:00:04 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * If the first argument is ".program" or "./program", this function will
 * append to the current directory and check if it is executable
 */
char	*relative_path(char *cmd)
{
	char	*temp;
	char	*append_path;
	char	*full_path;
	char	cwd[PATH_MAX];

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		temp = getcwd(cwd, sizeof(cwd));
		append_path = ft_strjoin(temp, "/");
		if (!append_path)
			return (NULL);
		full_path = ft_strjoin(append_path, cmd);
		free(append_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		return (NULL);
	}
	return (NULL);
}

char	*search_path(char *cmd, char **paths)
{
	char	*full_path;
	char	*append_cmd;
	int		i;

	i = 0;
	while (paths[i])
	{
		append_cmd = ft_strjoin(paths[i], "/");
		if (!append_cmd)
			return (free_array(paths), NULL);
		full_path = ft_strjoin(append_cmd, cmd);
		free(append_cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_mshell *shell)
{
	char	*path_var;
	char	**paths;
	char	*full_path;

	full_path = relative_path(cmd);
	if (full_path)
		return (full_path);
	path_var = get_env_value(shell->env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	full_path = search_path(cmd, paths);
	free_array(paths);
	return (full_path);
}
