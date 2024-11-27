/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:24:20 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/27 12:46:23 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_exit_status(t_mshell *shell, int status)
{
	shell->last_exit_status = status;
	return (0);
}

int	get_exit_status(t_mshell *shell)
{
	return (shell->last_exit_status);
}
