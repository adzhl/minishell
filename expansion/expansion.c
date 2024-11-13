/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:59:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/13 13:25:52 by etien            ###   ########.fr       */
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
// By default, the quote context ('initial_quote') is null, meaning no quotes
// are active. When the first quote is detected, it opens a quote context
// (setting 'initial_quote'). The context only closes when an identical closing
// quote is found. Non-matching quotes within an active context are ignored
// (do not change 'initial_quote').
// Behavior within each context:
// - In a single-quote context: everything is treated literally (no expansions).
// - In a double-quote context: variable expansions are allowed.
// Using the various states of `initial_quote` and `in_quote_context`,
// the function correctly processes nested and mixed quotes, performing
// expansions as required. The function returns a new string with
// variables expanded as specified by the quotes.
char	*expand_var(char *s)
{
	char	initial_quote;
	int		in_quote_context;
	char	*expanded_s;

	initial_quote = '\0';
	in_quote_context = 0;
	expanded_s = ft_strdup("");
	if (!expanded_s)
		return (NULL);
	while (*s)
	{
		expansion_control(&s, &initial_quote, &in_quote_context, &expanded_s);
		if (!expanded_s)
			return (NULL);
	}
	if (in_quote_context)
		return (perror(UNCLOSED_QUOTES), free(expanded_s), NULL);
	return (expanded_s);
}

// This function contains the main logic of expand_var.
// It handles the toggling of the quote variables whenever a single
// or double quote is encountered and decides whether to substitute
// in expanded variables or append strings to the expanded string.
void	expansion_control(char **s, char *initial_quote,
		int *in_quote_context, char **expanded_s)
{
	if ((**s == '\'' || **s == '\"') && !(*in_quote_context))
	{
		*initial_quote = **s;
		*in_quote_context = 1;
		(*s)++;
	}
	else if (**s == *initial_quote && *in_quote_context)
	{
		*initial_quote = '\0';
		*in_quote_context = 0;
		(*s)++;
	}
	else if ((**s == '$') && ((*in_quote_context && *initial_quote == '\"')
			|| (!(*in_quote_context) && *initial_quote == '\0')))
		*expanded_s = sub_in_var(s, *expanded_s);
	else
		*expanded_s = append_str(s, *expanded_s, ARGUMENT, *initial_quote);
}
