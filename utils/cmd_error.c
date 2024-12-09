/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:29:57 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/09 22:39:43 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function that prints out error message when cmd is not found and exits
 */
void	cmd_error(char *cmd_path, t_exec_cmd *ecmd, t_mshell *shell, int mode)
{
	if (mode)
		free(cmd_path);
	ft_putstr_fd(EXEC_ERR, STDERR_FILENO);
	ft_putendl_fd(ecmd->argv[0], STDERR_FILENO);
	set_exit_status(shell, 127);
	exit(127);
}
