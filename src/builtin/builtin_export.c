/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:58:14 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/12 11:31:27 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/**
 * Function to add new var to env list
 * Allocate space according to current env list + new var + NULL
 */
static int	add_to_env(char **env, const char *new_var)
{
    int	i;

    i = get_env_size(env);
    if (!(env[i] = ft_strdup(new_var)))
        return (0);
    env[i + 1] = NULL;
    return (1);
}

/**
 * 1. Replace '=' with '\0' so that we can check variable name
 * 2. If valid, replace back the '='
 * 3. If variable already exists, find index of variable and replace value
 * 4. Else, call add_to_env to allocate a new space to add the new var
 */
static int	handle_equal(char **env, char *arg, char *equal_sign)
{
    char	var_name[PATH_MAX];
    int		name_len;

    name_len = equal_sign - arg;
    ft_strlcpy(var_name, arg, name_len + 1);
    if (!valid_var_name(var_name))
    {
        print_export_error(arg);
        return (1);
    }
    if (!update_env_value(env, var_name, equal_sign + 1))
        return (add_to_env(env, arg));
    return (0);
}

int	builtin_export(char **args, char **env)
{
    int		i;
    char	*equal_sign;

    if (!args[1])
        return (print_sorted_env(env));
    i = 0;
    while (args[++i])
    {
        equal_sign = ft_strchr(args[i], '=');
        if (equal_sign && handle_equal(env, args[i], equal_sign))
            return (1);
        else if (!equal_sign && !valid_var_name(args[i]))
        {
            print_export_error(args[i]);
            return (1);
        }
    }
    return (0);
}

#include "../../include/builtin.h"

int main()
{
    // Pre-allocate environment with extra space
    // Size calculation: initial vars (2) + space for new vars (10) + NULL terminator (1)
    char **env = malloc(sizeof(char *) * 13);
    
    // Initialize with starting variables
    env[0] = ft_strdup("PATH=/usr/bin");
    env[1] = ft_strdup("HOME=/home/user");
    env[2] = NULL;  // Important: NULL terminate the array

    printf("Test 1: Print initial environment\n");
    char *args1[] = {"export", NULL};
    int result = builtin_export(args1, env);
    printf("Result: %d\n\n", result);

    printf("Test 2: Add new variable\n");
    char *args2[] = {"export", "NEW_VAR=value", NULL};
    result = builtin_export(args2, env);
    printf("Result: %d\n", result);
    printf("Updated environment:\n");
    char *args_print[] = {"export", NULL};
    builtin_export(args_print, env);
    printf("\n");

    printf("Test 3: Update existing variable\n");
    char *args3[] = {"export", "NEW_VAR=updated_value", NULL};
    result = builtin_export(args3, env);
    printf("Result: %d\n", result);
    printf("Updated environment:\n");
    builtin_export(args_print, env);
    builtin_env(NULL, env);
    printf("\n");

    printf("Test 4: Invalid variable\n");
    char *args4[] = {"export", "2INVALID=value", NULL};
    result = builtin_export(args4, env);
    printf("Result: %d\n\n", result);

    // Clean up
    int i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);

    return 0;
}