/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:26 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/10 14:52:30 by abinti-a         ###   ########.fr       */
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
		rl_clear_history();
	}
}

void	setup_signal_handling(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal_heredoc(t_mshell *shell, int status)
{
	int	sig;

	signal(SIGINT, handle_signal);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			set_exit_status(shell, 130);
	}
	else
		set_exit_status(shell, 0);
}

void	handle_child_exit(int status, t_mshell *shell)
{
	int	sig;

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
