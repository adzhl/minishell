/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:20:40 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/16 07:54:30 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parser.h"

// Run command functions
void	run_cmd(t_cmd *cmd, t_mshell *shell);
void	set_pipe(t_pipe_cmd *pcmd, t_mshell *shell);
void	set_redirection(t_redir_cmd *rcmd, t_mshell *shell);
void	open_fd(t_redir_cmd *rcmd);
void	pipe_heredoc(t_redir_cmd *rcmd);

// Run command util functions
void	run_cmd_control(char *input, t_cmd *ast, t_mshell *shell);
void	run_builtin(t_cmd *cmd, t_mshell *shell);
char	*get_standalone_cmd(t_cmd *ast);
void	close_pipes(int *pipefd);
void	cmd_typecasting(t_cmd *cmd,
			t_pipe_cmd **pcmd, t_redir_cmd **rcmd, t_exec_cmd **ecmd);

#endif