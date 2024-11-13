/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:49:49 by etien             #+#    #+#             */
/*   Updated: 2024/11/13 13:06:39 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This is an expansion helper function for appending non-expanding sections
// of the input string to the expanded string. The function will update the
// pointer position of its input string.
// There are three modes for appending: ARGUMENT, DELIMITER AND HEREDOC.
char	*append_str(char **s, char *expanded_s, int mode, char initial_quote)
{
	char	*start;
	char	*append_s;
	char	*joined_s;

	start = *s;
	append_s = NULL;
	if (!**s)
		return (free(expanded_s), NULL);
	if (mode == ARGUMENT)
		append_s = append_for_argument(s, initial_quote);
	else if (mode == DELIMITER)
		append_s = append_for_delimiter(s, initial_quote);
	else if (mode == HEREDOC)
		append_s = append_for_heredoc(s);
	if (!append_s)
		return (free(expanded_s), NULL);
	joined_s = ft_strjoin(expanded_s, append_s);
	free(append_s);
	if (!joined_s)
		return (free(expanded_s), NULL);
	free(expanded_s);
	return (joined_s);
}

// The length of string to be appended will depend on the quote context:
// 1) No quotes: Until a quote or $ sign is encountered
// 2) Single quotes: Until another single quote is encountered
// 3) Double quotes: Until another double quote or $ sign is encountered
char	*append_for_argument(char **s, char initial_quote)
{
	char	*start;

	start = *s;
	while (**s)
	{
		if ((initial_quote == '\0'
				&& (**s == '\'' || **s == '\"' || **s == '$'))
			|| (initial_quote == '\'' && **s == '\'')
			|| (initial_quote == '\"' && (**s == '\"' || **s == '$')))
			break ;
		(*s)++;
	}
	return (ft_substr(start, 0, *s - start));
}

// 1) No quotes: Until a quote is encountered.
// 2) Single/double quote: Until the matching quote is encountered.
char	*append_for_delimiter(char **s, char initial_quote)
{
	char	*start;

	start = *s;
	while (**s)
	{
		if ((initial_quote == '\0' && (**s == '\'' || **s == '\"'))
			|| (**s == initial_quote))
			break ;
		(*s)++;
	}
	return (ft_substr(start, 0, *s - start));
}

// Quote context is irrelevant for heredoc expansion.
// Length of appended string will be up until $ sign is encountered.
char	*append_for_heredoc(char **s)
{
	char	*start;

	start = *s;
	while (**s && **s != '$')
		(*s)++;
	return (ft_substr(start, 0, *s - start));
}
