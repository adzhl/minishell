/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:56:35 by etien             #+#    #+#             */
/*   Updated: 2024/11/18 17:42:08 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	syntax_error(char *input)
{
	char	*s;
	int		prev_tok;
	int		tok;

	prev_tok = 0;
	tok = 0;
	if (!quotes_are_closed(input))
		return (print_error(SYNTAX_QUOTES, input, NULL), true);
	s = ft_strdup(input);
	while (*s)
	{
		prev_tok = tok;
		tok = get_token(&s, s + ft_strlen(s), NULL, NULL);
		if ((tok == '|' && prev_tok != 'w')
				|| tok == '|' && prev_tok == '|')
			return (print_error(SYNTAX_PIPE, input, s), true);
		else if (ft_strchr("<>+-", (char)prev_tok) && tok != 'w')
			return (print_error(SYNTAX_REDIR, input, s), true);
	}
	free(s);
	return (false);
}

// This function will print an error message to STDERR and exit the program.
void	print_error(char *err_msg, char *input, char *s)
{
	ft_putendl_fd(err_msg, STDERR_FILENO);
	free(input);
	if (s)
		free(s);
}
