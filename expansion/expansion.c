/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:59:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/18 13:18:07 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TO-DO: have a way to store exit status of the last executed command
// so that it can be expanded when $? is called.
// $? is neither global nor stored in ENV.
// Bash keeps it as part of the shell's internal state.
// ChatGPT recommended creating a shell_state_struct that will contain
// last command exit status, environment variables, current working
// directory, etc.

// This function is responsible for expanding arguments and will involve both:
// - Literal expansion: removal of outside quotes
// - Variable expansion: substitution of variables
// The function expands variables in the input string based on quote contexts.
// By default, the quote context ('opening_quote') is null, meaning no quotes
// are active. When the first quote is detected, it opens a quote context
// (setting 'opening_quote'). The context only closes when an identical closing
// quote is found. Non-matching quotes within an active context are ignored
// (do not change 'opening_quote').
// Behavior within each context:
// - In a single-quote context: everything is treated literally (no expansions).
// - In a double-quote context: variable expansions are allowed.
// Using the various states of `opening_quote` and `in_quote`,
// the function correctly processes nested and mixed quotes, performing
// expansions as required. The function returns a new string with
// variables expanded as specified by the quotes.
char	*expand_argument(char *s)
{
	char	opening_quote;
	int		in_quote;
	char	*expanded_s;

	opening_quote = 0;
	in_quote = 0;
	expanded_s = ft_strdup("");
	if (!expanded_s)
		return (NULL);
	while (*s)
	{
		expansion_control(&s, &opening_quote, &in_quote, &expanded_s);
		if (!expanded_s)
			return (NULL);
	}
	return (expanded_s);
}

// This function contains the main logic of expand_argument.
// It handles the toggling of the quote variables whenever a single
// or double quote is encountered and decides whether to substitute
// in expanded variables or append strings to the expanded string.
void	expansion_control(char **s, char *opening_quote,
		int *in_quote, char **expanded_s)
{
	if ((**s == SQ || **s == DQ) && !(*in_quote))
	{
		*opening_quote = **s;
		*in_quote = 1;
		(*s)++;
	}
	else if (**s == *opening_quote && *in_quote)
	{
		*opening_quote = 0;
		*in_quote = 0;
		(*s)++;
	}
	else if ((**s == '$') && ((*in_quote && *opening_quote == DQ)
			|| (!(*in_quote) && !(*opening_quote))))
		*expanded_s = sub_in_var(s, *expanded_s);
	else
		*expanded_s = append_str(s, *expanded_s, EXP_ARGUMENT, *opening_quote);
}

// This function will expand the heredoc.
// Heredoc expansion ignores quotes (treats them as any other character)
// and only performs variable expansion.
// A local pointer will preserve the starting pointer to the original heredoc.
// The function will return the expanded heredoc and free the original heredoc.
char	*expand_heredoc(char *hd)
{
	char	*expanded_hd;
	char	*s;

	expanded_hd = ft_strdup("");
	if (!hd)
		return (expanded_hd);
	s = hd;
	while (*s)
	{
		if (*s == '$')
			expanded_hd = sub_in_var(&s, expanded_hd);
		else
			expanded_hd = append_str(&s, expanded_hd, EXP_HEREDOC, 0);
	}
	return (free(hd), expanded_hd);
}
