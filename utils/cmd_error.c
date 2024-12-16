/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:29:57 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/16 09:34:29 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function that prints out error message when cmd is not found and exits
 */
void	cmd_error(char *cmd_path, t_exec_cmd *ecmd, int mode)
{
	if (ecmd->argv[0][0] == '/' || (ecmd->argv[0][0] == '.'
			&& ecmd->argv[0][1] == '/'))
	{
		if (access(ecmd->argv[0], F_OK) == 0)
		{
			ft_putstr_fd(NO_ACCESS, STDERR_FILENO);
			ft_putendl_fd(ecmd->argv[0], STDERR_FILENO);
			exit(126);
		}
	}
	if (cmd_path)
		free(cmd_path);
	ft_putstr_fd(EXEC_ERR, STDERR_FILENO);
	ft_putendl_fd(ecmd->argv[0], STDERR_FILENO);
	if (mode)
		exit(EXIT_FAILURE);
	exit(127);
}
