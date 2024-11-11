/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:54:05 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/11 08:04:09 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

char **create_env_copy(char **envp)
{
    int     i;
    char    **env_copy;
    
    i = 0;
    while (envp[i])
        i++;
    env_copy = malloc(sizeof(char *) * (i + 1));
    if (!env_copy)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        env_copy[i] = ft_strdup(envp[i]);
        if (!env_copy[i])
        {
            while (--i >= 0)
                free(env_copy[i]);
            free(env_copy);
            return (NULL);
        }
        i++;
    }
    env_copy[i] = NULL;
    return (env_copy);
}
