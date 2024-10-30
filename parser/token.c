/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:51:34 by etien             #+#    #+#             */
/*   Updated: 2024/10/30 17:59:21 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// @param ss Pointer to start of the scan.
// @param es Pointer to end of the scan, i.e. end of the input buffer.
// @param st Pointer to start of the token. (Optional)
// @param et Pointer to end of the token. (Optional)
// @brief
// This function will:
// 1) skip over leading whitespace
// 2) detect for tokens (|, <, >, >> ('+') or words ('w'))
// 3) mark position of tokens (st and et)
// 4) skip over trailing whitespace
// 5) update start of scan pointer
// 6) return the token as an int
// Across multiple calls, it will grab the next token in the input.
// @return ASCII integer value of the token detected.
// @note
// Double pointers are used to update the positions of the input buffer
// pointers. A local pointer is created and walked along the input buffer.
// The local pointer's position is then copied over to the input buffer/
// token pointers.
// If the st and et parameters are set to NULL, this function will just
// update the scan space to begin at the next token.
// st and et parameters are usually only relevant if the token is 'w'
// because we will want to capture the entire word for string manipulation.
int	get_token(char **ss, char *es, char **st, char **et)
{
	char	*s;
	int		tok;

	s = *ss;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (st)
		*st = s;
	tok = *s;
	detect_token(&tok, &s, es);
	if (et)
		*et = s;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ss = s;
	return (tok);
}

// Outsourced get_token control structure to fit line count.
// This function advances the s pointer beyond the token and
// updates tok when the token is ">>" (+) or a word (w).
// A word is defined as anything that is non-whitespace and
// non-symbol.
void	detect_token(int *tok, char **s, char *es)
{
	if (**s == 0)
		return ;
	else if (**s == '|' || **s == '<')
		(*s)++;
	else if (**s == '>')
	{
		(*s)++;
		if (**s == '>')
		{
			*tok = '+';
			(*s)++;
		}
	}
	else
	{
		*tok = 'w';
		while (*s < es && !ft_strchr(WHITESPACE, **s)
			&& !ft_strchr(SYMBOLS, **s))
			(*s)++;
	}
}

// Originally named peek().
// This function works as a lookahead.
// It advances past leading whitespace and returns an int boolean for whether
// the token matches the string of tokens given in the parameter.
// *s check in the boolean evaluation is necessary just in case s is advanced
// to the null terminator, since it would evaluate to 0.
// The function is ideal for use with conditional structures to confirm
// the existence of certain tokens before deciding on further actions.
// The ss pointer is updated with the local pointer after skipping whitespace.
// @param ss Pointer to start of the scan.
// @param es Pointer to end of the scan, i.e. end of the input buffer.
// @param toks String of token characters you want to look ahead for.
int	check_for_token(char **ss, char *es, char *toks)
{
	char	*s;

	s = *ss;
	while (*s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ss = s;
	return (*s && ft_strchr(toks, *s));
}
