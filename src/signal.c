/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:26 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/06 14:41:35 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

void handle_signal(int signum)
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

void setup_signal_handling(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, SIG_IGN);
}
