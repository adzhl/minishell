/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:26:13 by etien             #+#    #+#             */
/*   Updated: 2024/12/02 11:37:56 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will first advance past the $ sign then check for
// three special cases of variable expansion:
// 1) $? is not an ENV but should expand to the exit status of the last
//    executed process.
// 2) $(digit) should expand to nothing.
// 3) $ on its own should be treated as a string literal.
// If the three checks are passed, the variable complies with the
// VAR format. We then check for its existence in our local ENV copy.
// If the variables exists, it will be appended to the expanded string.
// Otherwise, nothing is appended.
// Note: We don't have to free var_value because it is a pointer to our
//       local ENV copy that will be freed in the main function.
char	*sub_in_var(char **s, char *expanded_s, t_mshell *shell)
{
	char	*start;
	char	*var_name;
	char	*var_value;

	(*s)++;
	if (**s == '?')
		return (append_exit_status(s, expanded_s, shell));
	if (ft_isdigit(**s))
		return ((*s)++, expanded_s);
	if (!(ft_isalnum(**s) || **s == '_'))
		return (append_expansion(expanded_s, "$"));
	start = *s;
	while (**s && (ft_isalnum(**s) || **s == '_'))
		(*s)++;
	var_name = ft_substr(start, 0, *s - start);
	var_value = get_env_value(shell->env, var_name);
	free(var_name);
	if (!var_value)
		return (expanded_s);
	return (append_expansion(expanded_s, var_value));
}

// This is a helper function for appending the expansion to the
// expanded string. It works for appending a static string to a
// dynamically-allocated string.
char	*append_expansion(char *expanded_s, char *expansion)
{
	char	*joined_s;

	joined_s = ft_strjoin(expanded_s, expansion);
	free(expanded_s);
	return (joined_s);
}

// This function will pull the exit status from the shell struct
// and append it to the expanded string.
// Since ft_itoa returns dynamically-allocated memory, we have
// to free it after appending the string.
char	*append_exit_status(char **s, char *expanded_s, t_mshell *shell)
{
	char	*exit_status;

	(*s)++;
	exit_status = ft_itoa(get_exit_status(shell));
	expanded_s = append_expansion(expanded_s, exit_status);
	free(exit_status);
	return (expanded_s);
}

// This function will check that the input string has closed quotes.
// The bash shell checks for closed quotes on the entire input string
// rather than individual tokens.
// e.g. try running "cat "hello' | cat " hello".
bool	quotes_are_closed(char *s)
{
	char	opening_quote;

	opening_quote = 0;
	while (*s)
	{
		if (!opening_quote && (*s == SQ || *s == DQ))
			opening_quote = *s;
		else if (opening_quote && *s == opening_quote)
			opening_quote = 0;
		s++;
	}
	if (opening_quote)
		return (false);
	return (true);
}
