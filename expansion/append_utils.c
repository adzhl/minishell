/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:49:49 by etien             #+#    #+#             */
/*   Updated: 2024/11/13 16:56:56 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This is an expansion helper function for appending non-expanding sections
// of the input string to the expanded string. The function will update the
// pointer position of its input string.
// There are three modes for appending: ARGUMENT, DELIMITER AND HEREDOC.
char	*append_str(char **s, char *expanded_s, int mode, char opening_quote)
{
	char	*start;
	char	*append_s;
	char	*joined_s;

	start = *s;
	append_s = NULL;
	if (!**s)
		return (free(expanded_s), NULL);
	if (mode == EXP_ARGUMENT)
		append_s = append_for_argument(s, opening_quote);
	else if (mode == EXP_DELIMITER)
		append_s = append_for_delimiter(s, opening_quote);
	else if (mode == EXP_HEREDOC)
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
char	*append_for_argument(char **s, char opening_quote)
{
	char	*start;

	start = *s;
	while (**s)
	{
		if ((!opening_quote && (**s == SQ || **s == DQ || **s == '$'))
			|| (opening_quote == SQ && **s == SQ)
			|| (opening_quote == DQ && (**s == DQ || **s == '$')))
			break ;
		(*s)++;
	}
	return (ft_substr(start, 0, *s - start));
}

// 1) No quotes: Until a quote is encountered.
// 2) Single/double quotes: Until the matching quote is encountered.
char	*append_for_delimiter(char **s, char opening_quote)
{
	char	*start;

	start = *s;
	while (**s)
	{
		if ((!opening_quote && (**s == SQ || **s == DQ))
			|| (**s == opening_quote))
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
