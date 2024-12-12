/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:32:27 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/12 14:43:51 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_exec(t_mshell *shell, t_exec_cmd *ecmd)
{
	char	*cmd_path;

	shift_argv(ecmd);
	if (!ecmd->argv[0])
		return ;
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

// If argv[0] is an empty string, the while loop will shift the
// argument array to skip past it.
void	shift_argv(t_exec_cmd *ecmd)
{
	int	i;

	i = 0;
	if (ecmd->argv[0] && ft_strcmp(ecmd->argv[0], "") == 0)
	{
		free(ecmd->argv[0]);
		while (ecmd->argv[i])
		{
			ecmd->argv[i] = ecmd->argv[i + 1];
			i++;
		}
	}
}
