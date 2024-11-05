/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:59:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/05 11:10:59 by etien            ###   ########.fr       */
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

// This function expands variables in the input string based on quote contexts.
// By default, the quote context (`initial_quote`) is null, meaning no quotes are active.
// When the first quote is detected, it opens a quote context (setting `initial_quote`).
// The context only closes when an identical closing quote is found.
// Non-matching quotes within an active context are ignored (do not change `initial_quote`).
// Behavior within each context:
// - In a single-quote context: everything is treated literally (no expansions).
// - In a double-quote context: variable expansions are allowed.
// Using the various states of `initial_quote` and `in_quote_context`, the function
// correctly processes nested and mixed quotes, performing expansions as required.
// The function returns a new string with variables expanded as specified by the quotes.
char	*expand_var(char *s)
{
	char	initial_quote;
	int		in_quote_context;
	char	*expanded_s;

	initial_quote = '\0';
	in_quote_context = 0;
	expanded_s = ft_strdup("");
	if (!expanded_s)
		return (s);
	while (*s)
	{
		if ((*s == '\'' || *s == '\"') && !in_quote_context)
		{
			initial_quote = *s;
			in_quote_context = 1;
		}
		else if (*s == initial_quote && in_quote_context)
		{
			initial_quote = '\0';
			in_quote_context = 0;
		}
		else if ((*s == '$') && ((in_quote_context && initial_quote == '\"')
			|| (!in_quote_context && initial_quote == '\0')))
		{
			expanded_s = sub_in_var(&s, expanded_s);
			s--;
			printf("Expanded input after calling sub_in_var: %s\n", expanded_s);
		}
		else
		{
			expanded_s = append_str(&s, expanded_s, initial_quote);
			s--;
			 printf("Expanded input after calling append_str: %s\n", expanded_s);
		}
		s++;
	}
	if (in_quote_context)
		return (perror(UNCLOSED_QUOTES), free(expanded_s), NULL);
	return (expanded_s);
}

// This function will advance past the $ sign then check for the variable
// in ENV. If it exists, it will substitute in the variable by appending
// it to the expanded string.
// Note that getenv returns a pointer to static memory, so it does not
// have to be freed. If the variable does not exist in ENV, getenv
// simply returns a NULL pointer.
char	*sub_in_var(char **s, char *expanded_s)
{
	char	*start;
	char	*var_name;
	char	*var_value;
	char	*joined_s;

	(*s)++;
	printf("Processing variable after $: ");
	start = *s;
	if (ft_isdigit(**s))
	{
		(*s)++;
		return (expanded_s);
	}
	while (**s && (ft_isalnum(**s) || **s == '_'))
	{
		printf("%c", **s);
		(*s)++;
	}
	printf("'\n");
	var_name = ft_substr(start, 0, *s - start);
	if (!var_name)
		return (expanded_s);
	printf("Extracted variable name: '%s'\n", var_name);
	var_value = getenv(var_name);
	printf("Value of variable '%s': '%s'\n", var_name, var_value);
	free(var_name);
	if (!var_value)
		return (expanded_s);
	joined_s = ft_strjoin(expanded_s, var_value);
	if (!joined_s)
		return (expanded_s);
	free(expanded_s);
	return (joined_s);
}

// This function will append non-expanding sections of the input string
// to the expanded string and update the pointer's position in the
// expand_var function.
// The length of string to be appended will depend on the quote context:
// 1) No quotes: Until a quote or $ sign is encountered
// 2) Single quotes: Until another single quote is encountered
// 3) Double quotes: Until another double quote or $ sign is encountered
char	*append_str(char **s, char *expanded_s, char initial_quote)
{
	char	*start;
	char	*append_s;
	char	*joined_s;

	start = *s;
	if (!**s)
		return (expanded_s);
	while (**s)
	{
		if ((initial_quote == '\0' && (**s == '\'' || **s == '\"' || **s == '$'))
			|| (initial_quote == '\'' && **s == '\'')
			|| (initial_quote == '\"' && (**s == '\"' || **s == '$')))
			break ;
		(*s)++;
	}
	append_s = ft_substr(start, 0, *s - start);
	printf("Appending from: '%s'\n", append_s);
	if (!append_s)
		return (expanded_s);
	joined_s = ft_strjoin(expanded_s, append_s);
	free(append_s);
	if (!joined_s)
		return (expanded_s);
	printf("After append, expanded_s: '%s'\n", joined_s);
	free(expanded_s);
	return (joined_s);
}
