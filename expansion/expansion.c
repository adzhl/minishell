/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:59:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/01 18:03:17 by etien            ###   ########.fr       */
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

// This function will expand the variables in the input after considering
// the precedence of single quotes, double quotes or the absence of any quotes.
// Two booleans, in_sq (in single quotes) and in_dq (in double quotes) are set
// to false by default. The pointer is then walked along the string.
// At any given time, only one boolean can be set to true to indicate the
// outermost quote when there are nested quotes. This type of quote will have
// precedence and will control whether expansion happens.
// Variables expand only when they are not within single quotes.
// A boolean that has been set to true can only be toggled false when the same
// type of quote is encountered again. This will enable to function to detect
// unclosed quotes and trigger the necessary syntax error.
// The function will return the input with expanded variables substituted in.
char	*expand_var(char *s)
{
	bool	in_sq;
	bool	in_dq;
	char	*expanded_s;

	in_sq = false;
	in_dq = false;
	expanded_s = ft_strdup("");
	if (!expanded_s)
		return (s);
	while (*s)
	{
		printf("Processing: '%c', in_sq: %d, in_dq: %d\n", *s, in_sq, in_dq);
		if ((*s == '\'') && !in_dq)
			in_sq = !in_sq;
		else if ((*s == '\"') && !in_sq)
			in_dq = !in_dq;
		else if ((*s == '$') && !in_sq)
		{
			expanded_s = sub_in_var(&s, expanded_s);
			s--;
			printf("Expanded input after calling sub_in_var: %s\n", expanded_s);
		}
		else
		{
			expanded_s = append_str(&s, expanded_s);
			s--;
			 printf("Expanded input after calling append_str: %s\n", expanded_s);
		}
		s++;
	}
	if (in_sq || in_dq)
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
	while (**s && !ft_strchr(WHITESPACE, **s) && **s != '\''
		&& **s != '\"' && **s != '$')
	{
		printf("%c", **s);
		(*s)++;
	}
	printf("'\n");
	var_name = ft_substr(start, 0, *s - start);
	printf("Extracted variable name: '%s'\n", var_name);
	if (!check_var_name(var_name))
	{
		free(var_name);
		printf("Invalid variable name: '%s'\n", var_name);
		return (expanded_s);
	}
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
char	*append_str(char **s, char *expanded_s)
{
	char	*start;
	char	*append_s;
	char	*joined_s;

	start = *s;
	if (!**s)
		return (expanded_s);
	while (**s && **s != '\'' && **s != '\"' && **s != '$')
		(*s)++;
	append_s = ft_substr(start, 0, *s - start);
	printf("Appending from: '%s'\n", append_s);
	if (!append_s)
		return (expanded_s);
	joined_s = ft_strjoin(expanded_s, append_s);
	if (!joined_s)
		return (expanded_s);
	printf("After append, expanded_s: '%s'\n", joined_s);
	free(expanded_s);
	free(append_s);
	return (joined_s);
}

// This function checks that the variable name has a valid syntax
// before it can be passed to getenv.
// It returns true if the syntax is valid or false otherwise.
// $VAR should not start with underscores or digits.
// The rest of the $VAR should be composed of alphanumeric characters
// and underscores only.
bool	check_var_name(char *s)
{
	if (!s || *s == '_' || ft_isdigit(*s))
		return (false);
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (false);
		s++;
	}
	return (true);
}
