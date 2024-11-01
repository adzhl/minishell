/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:59:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/01 12:37:11 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TO-DO: have a way to store exit status of the last executed command
// so that it can be expanded when $? is called.
// $? is neither global nor stored in ENV.
// Bash keeps it as part of the shell's internal state.
// ChatGPT recommended creating a shell_state_struct that will contain
// last command exit status, environment variables, current working directory etc.

// This function will expand the variables in the input buffer after considering
// the precedence of single quotes, double quotes or the absence of any quotes.
// Two booleans to indicate if the string pointer is between quotes are used to
// toggle different actions.
// The input buffer with expanded variables is returned by the function.
// sq is short for single quotes (')
// dq is short for double quotes (")
char	*expansion(char *s)
{
	bool	in_sq;
	bool	in_dq;

	in_sq = false;
	in_dq = false;



}



// This function checks that the $VAR is in a valid syntax before calling getenv.
// It returns true if the syntax is valid or false otherwise.
// $VAR should not start with underscores or digits.
// The rest of the $VAR should be composed of alphanumeric characters and underscores only.
bool	check_var_name(char *s)
{
	if (!s || *s == '_' || ft_isdigit(*s))
		return (false);
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (false);
		s++;
	}
	return (true);
}
