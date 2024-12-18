/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtin_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:19:38 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/18 16:36:56 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_builtin_redir(t_redir_cmd *rcmd, t_mshell *shell)
{
	int	in;
	int	out;

	in = dup(STDOUT_FILENO);
	out = dup(STDIN_FILENO);
	if (rcmd->file)
		open_fd(rcmd);
	else if (rcmd->heredoc)
		pipe_heredoc(rcmd);
	run_builtin(rcmd->cmd, shell);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(out);
	close(in);
}
