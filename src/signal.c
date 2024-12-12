/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:26 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/12 16:06:09 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signal_handling(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_signal(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

void	handle_signal_heredoc(t_mshell *shell, int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			set_exit_status(shell, 130);
	}
	else if (WIFEXITED(status))
		set_exit_status(shell, WEXITSTATUS(status));
}

void	handle_child_exit(int status, t_mshell *shell)
{
	int	sig;

	if (shell->last_exit_status == 130)
		return ;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			set_exit_status(shell, 130);
		else if (sig == SIGQUIT)
		{
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
			set_exit_status(shell, 131);
		}
	}
	else if (WIFEXITED(status))
		set_exit_status(shell, WEXITSTATUS(status));
}
