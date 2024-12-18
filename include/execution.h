/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:20:40 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/18 17:38:41 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parser.h"

// Run command functions
void	run_cmd_control(char *input, t_cmd *ast, t_mshell *shell);
void	run_builtin(t_cmd *cmd, t_mshell *shell);
void	run_cmd(t_cmd *cmd, t_mshell *shell);

// PIPE node functions
void	set_pipe(t_pipe_cmd *pcmd, t_mshell *shell);
void	setup_child(int inputfd, int outputfd, int *pipefd);
void	close_pipes(int *pipefd);

// REDIR node functions
void	set_builtin_redir(t_redir_cmd *rcmd, t_mshell *shell);
void	set_redirection(t_redir_cmd *rcmd, t_mshell *shell);
void	open_fd(t_redir_cmd *rcmd);
void	pipe_heredoc(t_redir_cmd *rcmd);

// EXEC node functions
void	run_exec(t_mshell *shell, t_exec_cmd *ecmd);
void	shift_argv(t_exec_cmd *ecmd);

// Util functions
char	*get_standalone_cmd(t_cmd *ast);
void	cmd_typecasting(t_cmd *cmd,
			t_pipe_cmd **pcmd, t_redir_cmd **rcmd, t_exec_cmd **ecmd);

#endif
