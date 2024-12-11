/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:51:07 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/11 14:48:20 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	setup_child(int inputfd, int outputfd, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (inputfd)
		dup2(inputfd, STDIN_FILENO);
	if (outputfd)
		dup2(outputfd, STDOUT_FILENO);
	close_pipes(pipefd);
}
