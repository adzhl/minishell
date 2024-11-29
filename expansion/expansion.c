/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:59:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/29 14:46:08 by abinti-a         ###   ########.fr       */
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
// The function will return the dynamically-allocated expanded string and free
// the original string.
char	*expand_argument(char *s, t_mshell *shell)
{
	char	opening_quote;
	int		in_quote;
	char	*expanded_s;

	opening_quote = 0;
	in_quote = 0;
	expanded_s = ft_strdup("");
	while (*s)
	{
		if ((*s == SQ || *s == DQ) && !in_quote)
			toggle_quotes(&s, &opening_quote, &in_quote, OPENING_QUOTE);
		else if (*s == opening_quote && in_quote)
			toggle_quotes(&s, &opening_quote, &in_quote, CLOSING_QUOTE);
		else if (*s == '$' && ((in_quote && opening_quote == DQ)
				|| (!in_quote && !opening_quote)))
			expanded_s = sub_in_var(&s, expanded_s, shell);
		else
			expanded_s = append_str(&s, expanded_s, EXP_ARGUMENT, opening_quote);
	}
	return (expanded_s);
}

// This function handles the toggling of the quote variables whenever
// a single or double quote is encountered.
void	toggle_quotes(char **s, char *opening_quote, int *in_quote, int quote)
{
	if (quote == OPENING_QUOTE)
	{
		*opening_quote = **s;
		*in_quote = 1;
		(*s)++;
	}
	else if (quote == CLOSING_QUOTE)
	{
		*opening_quote = 0;
		*in_quote = 0;
		(*s)++;
	}
}

// This function will expand the heredoc.
// Heredoc expansion ignores quotes (treats them as any other character)
// and only performs variable expansion.
// A local pointer will preserve the starting pointer to the original heredoc.
// The function will return the expanded heredoc and free the original heredoc.
char	*expand_heredoc(char *hd, t_mshell *shell)
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
			expanded_hd = sub_in_var(&s, expanded_hd, shell);
		else
			expanded_hd = append_str(&s, expanded_hd, EXP_HEREDOC, 0);
	}
	return (free(hd), expanded_hd);
}
