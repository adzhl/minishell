/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:51:34 by etien             #+#    #+#             */
/*   Updated: 2024/10/29 18:13:50 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// @param ss Pointer to start of the scan.
// @param es Pointer to end of the scan, i.e. end of the input buffer.
// @param st Pointer to start of the token.
// @param et Pointer to end of the token.
// @brief
// This function will:
// 1) skip over leading whitespace
// 2) detect for tokens (|, <, >, >> (labelled as '+') or words (labelled as 'w'))
// 3) mark position of tokens (st and et)
// 4) skip over trailing whitespace
// 5) update start of scan pointer
// 6) return the token as an int
// @return ASCII integer value of the token detected.
// @note
// Double pointers are used to update the positions of the input buffer
// pointers. A local pointer is created and walked along the input buffer.
// The local pointer's position is copied over to the input buffer pointers.
int get_token(char **ss, char *es, char **st, char **et)
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



	return (tok);
}

// Outsourced get_token control structure to fit line count.
// This function advances the s pointer beyond the token and
// updates tok when the token is ">>" (+) or a word (w).
void detect_token(int *tok, char **s, char *es)
{
	if (**s == '|' || **s == '<')
		(*s)++;
	else if (**s == '>')
	{
		(*s)++;
		if  (**s == '>')
		{
			*tok = '+';
			(*s)++;
		}
	}
	else
	{
		*tok = 'w';
		while (*s < es && !ft_strchr(WHITESPACE, **s) && !ft_strchr(SYMBOLS, **s))
			(*s)++;
	}
}
