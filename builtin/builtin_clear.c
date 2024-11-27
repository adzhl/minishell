/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:24:46 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/27 10:37:35 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Function to clear the screen using ANSI escape sequence
 * \033 is the escape character (ASCII 27), which begins an ANSI
 * escape sequence.
 * [H moves the cursor to the top-left corner.
 * [J clears the screen from the cursor position to the end.
 */
int	builtin_clear(char **args, char **env)
{
	const char	*clear_sequence;

	(void)args;
	(void)env;
	clear_sequence = "\033[H\033[J";
	if (write(STDOUT_FILENO, clear_sequence, 6) == -1)
		return (1);
	return (0);
}
