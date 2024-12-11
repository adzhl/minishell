/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:32:27 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/11 09:03:13 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_exec(t_mshell *shell, t_exec_cmd *ecmd)
{
	char	*cmd_path;

	if (is_builtin(ecmd->argv[0]) && execute_builtin(ecmd->argv[0], ecmd->argv,
			shell) != 0)
		exit(EXIT_FAILURE);
	if (is_builtin(ecmd->argv[0]))
		exit(EXIT_SUCCESS);
	cmd_path = find_path(ecmd->argv[0], shell);
	if (!cmd_path)
		cmd_error(cmd_path, ecmd, 0);
	if (execve(cmd_path, ecmd->argv, shell->env) == -1)
		cmd_error(cmd_path, ecmd, 1);
	free(cmd_path);
}
