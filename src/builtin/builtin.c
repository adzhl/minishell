/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:28:56 by abinti-a          #+#    #+#             */
/*   Updated: 2024/10/29 14:18:33 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

/**
 * Initialize built-in commands table 
 * A library that stores a list of built-in commands
 */
/* t_builtin *init_builtin(void)
{
    static t_builtin builtins[] =
    {
        {"echo", builtin_echo},
        {"cd", builtin_cd},
        {"pwd", builtin_pwd},
        {"export", builtin_export},
        {"unset", builtin_unset},
        {"env", builtin_env},
        {"exit", builtin_exit},
        {NULL, NULL}
    };
    return (builtins);
} */

/**
 * Global built-in commands table 
 * A library that stores a list of built-in commands
 */
t_builtin g_builtins[] =
{
    {"echo", builtin_echo},
    {"cd", builtin_cd},
    {"pwd", builtin_pwd},
    {"export", builtin_export},
    {"unset", builtin_unset},
    {"env", builtin_env},
    {"exit", builtin_exit},
    {NULL, NULL}
};

/**
 * Check if cmd is a built-in
 */
int is_builtin(char *cmd)
{
    int i;

    i = 0;
    while (g_builtins[i].name)
    {
        if (!ft_strcmp(cmd, g_builtins[i].name))
            return (1);
        i++;
    }
    return (0);
}

/**
 * Execute built-in commands
 */
int execute_builtin(char *cmd, char **args, char **env)
{
    int i;

    i = 0;
    while (g_builtins[i].name)
    {
        if (!ft_strcmp(cmd, g_builtins[i].name))
            return (g_builtins[i].func(args, env));
        i++;
    }
    return (1);
}