/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:23:48 by etien             #+#    #+#             */
/*   Updated: 2024/12/18 17:40:18 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function contains the main logic for command execution.
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
		cmd_error(cmd_path, ecmd);
	if (execve(cmd_path, ecmd->argv, shell->env) == -1)
		cmd_error(cmd_path, ecmd);
	free(cmd_path);
}

// As long as argv[0] is an empty string, the while loop will keep
// shifting the argument array to skip past it.
void	shift_argv(t_exec_cmd *ecmd)
{
	int	i;

	i = 0;
	while (ecmd->argv[0] && ft_strcmp(ecmd->argv[0], "") == 0)
	{
		i = 0;
		free(ecmd->argv[0]);
		while (ecmd->argv[i])
		{
			ecmd->argv[i] = ecmd->argv[i + 1];
			i++;
		}
	}
}
