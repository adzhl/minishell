/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:24:23 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:30:14 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_exit_error(char *arg, char *message)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}

/**
 * Skip over '-' and '+' if any
 * Check if the string contains only numbers
 */
static int	is_numeric(const char *str)
{
	int	i;

	if (*str == '-' || *str == '+')
		str++;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * 1. Print out "exit\n"
 * 2. Check for arguments. If no arguments, exit with exit code 0
 * 3. Check if the argument is numeric
 * 4. Check if there is more than one argument
 * 5. Exit the program with the exit code from the argument
 * 6. Exit code range is 0 - 255 so other values will wrap around
 */
int	builtin_exit(char **args, t_mshell *shell)
{
	int	exit_code;
	int	exit_return;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args[1])
	{
		set_exit_status(shell, 0);
		exit(0);
	}
	if (!is_numeric(args[1]))
	{
		print_exit_error(args[1], "numeric argument required");
		set_exit_status(shell, 255);
		exit(255);
	}
	if (args[2])
	{
		print_exit_error(NULL, "too many arguments");
		set_exit_status(shell, 1);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit_return = (unsigned char)(exit_code % 256);
	set_exit_status(shell, exit_return);
	return (exit_return);
}

// int	main(int argc, char *argv[], char *envp[]) {
// 	(void)argc;
// 	(void)argv;
// 	t_mshell shell;

// 	shell.last_exit_status = 0;
// 	printf("Exit status before: %d\n", get_exit_status(&shell));
// 	shell.env = copy_env(envp);
// 	char *testcase[] = {"exit", "123", NULL};
// 	int result = builtin_exit(testcase, &shell);
// 	printf("Exit status after: %d\n", get_exit_status(&shell));
// 	free_array(shell.env);
// 	return (result);
// }
