/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:26:13 by etien             #+#    #+#             */
/*   Updated: 2024/11/12 13:28:21 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will advance past the $ sign then first check for
// three exceptions to variable expansion:
// 1) $? is not an ENV but should expand to the exit status of the last
//    executed process.
// 2) $(digit) should expand to nothing.
// 3) $(non-$VAR format) should be replaced by '$' only
//    (treated as a string literal).
// If the three checks are passed, the variable complies with the
// VAR format. We then check for its existence in ENV.
// If the variables exists, it will be appended to the expanded string.
// Otherwise, nothing is appended.
// Note that getenv returns a pointer to static memory, so it does not
// have to be freed. If the variable does not exist in ENV, getenv
// simply returns a NULL pointer.
char	*sub_in_var(char **s, char *expanded_s)
{
	char	*start;
	char	*var_name;
	char	*var_value;

	(*s)++;
	if (**s == '?')
		return (append_exit_status(s, expanded_s));
	if (ft_isdigit(**s))
		return ((*s)++, expanded_s);
	if (!(ft_isalnum(**s) || **s == '_'))
		return (append_expansion(expanded_s, "$"));
	start = *s;
	while (**s && (ft_isalnum(**s) || **s == '_'))
		(*s)++;
	var_name = ft_substr(start, 0, *s - start);
	if (!var_name)
		return (free(expanded_s), NULL);
	var_value = getenv(var_name);
	free(var_name);
	if (!var_value)
		return (expanded_s);
	return (append_expansion(expanded_s, var_value));
}

// This is a helper function for appending the expansion to the
// input string. It works for appending a static string to a
// dynamically-allocated string.
char	*append_expansion(char *expanded_s, char *expansion)
{
	char	*joined_s;

	joined_s = ft_strjoin(expanded_s, expansion);
	if (!joined_s)
		return (free(expanded_s), NULL);
	free(expanded_s);
	return (joined_s);
}

// TO-DO: Link this function to access latest process exit code.
// This function will pull the exit status from the shell struct.
// Since ft_itoa returns dynamically-allocated memory, we have
// to free it after appending the string.
char	*append_exit_status(char **s, char *expanded_s)
{
	char	*exit_status;

	(*s)++;
	exit_status = ft_itoa(0);
	if (!exit_status)
		return (free(expanded_s), NULL);
	expanded_s = append_expansion(expanded_s, exit_status);
	free(exit_status);
	return (expanded_s);
}

// This function will append non-expanding sections of the input string
// to the expanded string and update the pointer's position in the
// expand_var function.
// The length of string to be appended will depend on the quote context:
// 1) No quotes: Until a quote or $ sign is encountered
// 2) Single quotes: Until another single quote is encountered
// 3) Double quotes: Until another double quote or $ sign is encountered
char	*append_str(char **s, char *expanded_s, int mode, char initial_quote)
{
	char	*start;
	char	*append_s;
	char	*joined_s;

	start = *s;
	if (!**s)
		return (free(expanded_s), NULL);
	while (**s)
	{
		if ((mode == ARGUMENT && ((initial_quote == '\0'
				&& (**s == '\'' || **s == '\"' || **s == '$'))
			|| (initial_quote == '\'' && **s == '\'')
			|| (initial_quote == '\"' && (**s == '\"' || **s == '$'))))
			|| (mode == DELIMITER && **s == initial_quote)
			|| (mode == HEREDOC && **s == '$' ))
			break ;
		(*s)++;
	}
	append_s = ft_substr(start, 0, *s - start);
	if (!append_s)
		return (free(expanded_s), NULL);
	joined_s = ft_strjoin(expanded_s, append_s);
	free(append_s);
	if (!joined_s)
		return (free(expanded_s), NULL);
	free(expanded_s);
	return (joined_s);
}
