/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:30:00 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/28 08:46:45 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *find_path(char *cmd, t_mshell *shell)
{
    char *path_var;
    char **paths;
    char *full_path;
    char *join_slash;
    int i;

    path_var = get_env_value(shell->env, "PATH");
    if (!path_var)
        return (NULL);
    paths = ft_split(path_var, ':');
    i = 0;
    while (paths[i])
    {
        join_slash = ft_strjoin(paths[i], "/");
        if (!join_slash)
            return (NULL);
        full_path = ft_strjoin(join_slash, cmd);
        if (access(full_path, F_OK | X_OK) == 0)
            return(free_array(paths), full_path);
        free(full_path);
        i++;
    }
    free_array(paths);
    return (NULL);
}
