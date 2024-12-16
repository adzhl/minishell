/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:56:35 by etien             #+#    #+#             */
/*   Updated: 2024/12/16 17:51:57 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will return true if the input consists entirely of
// whitespace so that the shell can reprompt the user.
bool	empty_line_error(char *input)
{
	char	*s;

	s = input;
	while (*s)
	{
		if (!ft_strchr(WHITESPACE, *s))
			return (false);
		s++;
	}
	return (free(input), true);
}

// This function will return true if syntax errors are detected
// in the input. The input is first duplicated, and the starting
// pointer to the duplicated string is preserved to free it later on.
// The syntax checks are:
// 1) Input must have closed quotes
// 2) Pipe token must be preceded by a word token (command)
// 3) Pipe tokens cannot occur back to back
// 4) Redirection must be followed by a word token (file name/EOF)
// 5) Pipe cannot be last token
// 6) Redirection cannot be last token
bool	syntax_error(char *input)
{
	char	*s;
	char	*original_s;
	int		prev_tok;
	int		tok;

	tok = -1;
	if (!quotes_are_closed(input))
		return (print_error(SYNTAX_QUOTES, input, NULL), true);
	s = ft_strdup(input);
	original_s = s;
	while (*s)
	{
		prev_tok = tok;
		tok = get_token(&s, s + ft_strlen(s), NULL, NULL);
		if ((tok == '|' && prev_tok != 'w')
			|| (tok == '|' && prev_tok == '|'))
			return (print_error(SYNTAX_PIPE, input, original_s), true);
		else if (ft_strchr("<>+-", (char)prev_tok) && tok != 'w')
			return (print_error(SYNTAX_REDIR, input, original_s), true);
	}
	if (ft_strchr("|", (char)tok))
		return (print_error(SYNTAX_PIPE, input, original_s), true);
	else if (ft_strchr("<>+-", (char)tok))
		return (print_error(SYNTAX_REDIR, input, original_s), true);
	return (free(original_s), false);
}

// This function will print an error message to STDERR then free the
// input and duplicated string.
void	print_error(char *err_msg, char *input, char *original_s)
{
	ft_putendl_fd(err_msg, STDERR_FILENO);
	free(input);
	if (original_s)
		free(original_s);
}
