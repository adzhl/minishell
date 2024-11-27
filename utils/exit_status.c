/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:24:20 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/27 10:39:09 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int set_exit_status(char **env, int status)
{
    char *status_str;
    int result;

    status_str = ft_itoa(status);
    if (!status_str)
        return (1);
    if (update_env_value(env, "EXIT_STATUS", status_str))
    {
        free(status_str);
        return (0);
    }
    result = add_to_env(env, "EXIT_STATUS");
    free(status_str);
    return (result);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    char **env_copy = create_env_copy(env);
    if (!env_copy)
    {
        perror("Failed to create environment copy");
        return (1);
    }
    if (set_exit_status(env_copy, 255) != 0)
    {
        perror("Failed to set exit status");
        return (1);
    }
    builtin_env(NULL, env_copy);
    free_array(env_copy);

    return (0);
}