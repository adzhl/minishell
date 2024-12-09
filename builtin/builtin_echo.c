/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:12:16 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/10 07:23:26 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Handle the case for:
 *
 * Single -n
 * Multiple -n
 * -nnnnnn
 *
 * Exclude: -nWord
 */
static int	handle_n_option(char **args, int *newline)
{
	int	i;
	int	j;

	i = 1;
	*newline = 1;
	while (args[i])
	{
		if (args[i][0] != '-')
			break ;
		if (args[i][1] != 'n')
			break ;
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		*newline = 0;
		i++;
	}
	return (i);
}

/**
 * Function prints out the string after echo is called
 * adds '\n' at the end of the last argument by default
 * if -n is present, no '\n' will be added
 * if argument is empty then only print out '\n'
 */
int	builtin_echo(char **args, t_mshell *shell)
{
	int		i;
	int		newline;

	i = handle_n_option(args, &newline);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	set_exit_status(shell, 0);
	return (0);
}

/* int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)env;
	builtin_echo(argv, NULL);
	return (0);
} */
