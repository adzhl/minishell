/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:12:16 by abinti-a          #+#    #+#             */
/*   Updated: 2024/10/31 12:43:29 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

/**
 * Function prints out the string after echo is called
 * adds '\n' at the end of the last argument by default
 * if -n is present, no '\n' will be added
 * if argument is empty then only print out '\n'
 */
int	builtin_echo(char **args, char **env)
{
	int	i;
	int	newline;

	(void)env;
	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

/* int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)env;
    builtin_echo(argv, NULL);
    return (0);
} */
