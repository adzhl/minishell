/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:04:01 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/03 10:00:22 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Shift the remaining variable after the one we removed to the left
 */
static void	remove_var(char **env, int index)
{
	free(env[index]);
	while (env[index])
	{
		env[index] = env[index + 1];
		index++;
	}
}

/**
 * Print error when variable name is not valid
 */
static void	print_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/**
 * 1. Check if there are any arguments
 * 2. Iterate through argument and check for valid variable name
 * 3. Find index containing variable name in env
 * 4. If found, remove variable from env
 * 5. Return (0) if successful
 */
int	builtin_unset(char **args, t_mshell *shell)
{
	int	i;
	int	var_index;

	set_exit_status(shell, 0);
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!valid_var_name(args[i]))
		{
			print_unset_error(args[i]);
			set_exit_status(shell, 1);
		}
		else
		{
			var_index = find_var_name(shell->env, args[i]);
			if (var_index != -1)
				remove_var(shell->env, var_index);
		}
		i++;
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_mshell shell;

// 	shell.env = copy_env(envp);
// 	printf("Initial env:\n");
// 	builtin_env(NULL, &shell);
// 	printf("\n");
// 	// printf("export list before:\n");
// 	// char *args2[] = {"export", NULL};
// 	// builtin_export(args2, &shell);
// 	// printf("\n");
// 	char *args1[] = {"unset", "testing", NULL};
// 	printf("env after:\n");
// 	builtin_unset(args1, &shell);
// 	builtin_env(NULL, &shell);
// 	printf("\n");
// 	// printf("export list after:\n");
// 	// builtin_export(args2, &shell);
// 	free_array(shell.env);
// 	return (0);
// }
