/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:59:56 by etien             #+#    #+#             */
/*   Updated: 2024/12/09 21:01:27 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
// The function will return a dynamically-allocated expanded string.
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
		else if (*s == '$' && ((in_quote && opening_quote == DQ) || (!in_quote
					&& !opening_quote)))
			expanded_s = sub_in_var(&s, expanded_s, shell);
		else
			expanded_s = append_str(&s, expanded_s, EXP_ARGUMENT,
					opening_quote);
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

// This function will expand each of the arguments in the argument array
// before the command is passed for execution. It will free the original
// argument and replace it with the expanded argument.
void	expand_argv(char **argv, t_mshell *shell)
{
	char	*expanded_arg;
	int		i;

	expanded_arg = NULL;
	i = 0;
	while (argv[i])
	{
		expanded_arg = expand_argument(argv[i], shell);
		free(argv[i]);
		argv[i] = expanded_arg;
		i++;
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
