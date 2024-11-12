/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:29:22 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/12 11:31:46 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	get_env_size(char **env)
{
    int	i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

static void sort_env(char **env_copy, int size)
{
    int     i;
    int     j;
    char    *tmp;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (ft_strcmp(env_copy[j], env_copy[j + 1]) > 0)
            {
                tmp = env_copy[j];
                env_copy[j] = env_copy[j + 1];
                env_copy[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

static char **copy_and_sort_env(char **env)
{
    int     i;
    int     size;
    char    **env_copy;

    size = get_env_size(env);
    env_copy = malloc(sizeof(char *) * (size + 1));
    if (!env_copy)
        return (NULL);
    i = 0;
    while (i < size)
    {
        env_copy[i] = ft_strdup(env[i]);
        if (!env_copy[i])
        {
            free_array(env_copy);
            return (NULL);
        }
        i++;
    }
    env_copy[i] = NULL;
    sort_env(env_copy, size);
    return (env_copy);
}

int print_sorted_env(char **env)
{
    char **env_copy;
    int i;

    env_copy = copy_and_sort_env(env);
    if (!env_copy)
        return (1);

    i = 0;
    while (env_copy[i])
    {
        printf("declare -x %s\n", env_copy[i]);
        i++;
    }
    free_array(env_copy);
    return (0);
}
