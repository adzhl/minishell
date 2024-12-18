/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:06:37 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/02 13:39:20 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function to print current working directory using getcwd from <unistd.h>
 * PATH_MAX <limits.h> : maximum allowable length for a path in the system
 */
int	builtin_pwd(char **args, t_mshell *shell)
{
	char	cwd[PATH_MAX];

	(void)args;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	set_exit_status(shell, 0);
	return (0);
}

/* int main(void)
{
    if (builtin_pwd(NULL, NULL) != 0)
    {
        printf("Error\n");
        return (1);
    }
    return (0);
} */
