/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:24:23 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/27 10:38:02 by abinti-a         ###   ########.fr       */
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
int	builtin_exit(char **args, char **env)
{
	int	exit_code;

	(void)env;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		print_exit_error(args[1], "numeric argument required");
		exit(255);
	}
	if (args[2])
	{
		print_exit_error(NULL, "too many arguments");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	return ((unsigned char)(exit_code % 256));
}

/* #include <stdio.h>

int	main(int argc, char *argv[], char *envp[]) {
	(void)argc;
	(void)argv;

	char *testcase[3] = {"exit", "10293409370", NULL};
	int result = builtin_exit(testcase, envp);
	if (result == 0)
		printf("Exit called successfully\n");
	else
		printf("Error\n");
	return (result);
} */
