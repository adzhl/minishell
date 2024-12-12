/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:29:57 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/12 12:21:00 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function that prints out error message when cmd is not found and exits
 */
void	cmd_error(char *cmd_path, t_exec_cmd *ecmd, int mode)
{
	if (mode)
		free(cmd_path);
	ft_putstr_fd(EXEC_ERR, STDERR_FILENO);
	ft_putendl_fd(ecmd->argv[0], STDERR_FILENO);
	if (mode)
		exit(1);
	exit(127);
}
