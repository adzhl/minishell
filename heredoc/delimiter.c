/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:04:12 by etien             #+#    #+#             */
/*   Updated: 2024/11/14 10:39:37 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will check if the delimiter contains quotes.
// If there are quotes, they will be removed and expand_hd will
// be set to false to prevent heredoc expansion.
// Regardless whether there are quotes, the function will always
// turn the delimiter into a dynamically-allocated string to
// standardize the cleaning-up process later on.
void	check_delimiter(char **eof, bool *expand_hd)
{
	if (!ft_strchr(*eof, SQ) && !ft_strchr(*eof, DQ))
		return ;
	*eof = remove_delimiter_quotes(*eof);
	*expand_hd = false;
}

// This function will remove the quotes from the delimiter so that the
// EOF will be correctly detected by the collect_heredoc_input function.
// The delimiter is modified by literal expansion only.
// The function returns a dynamically-allocated string.
char	*remove_delimiter_quotes(char *eof)
{
	char	*new_eof;
	char	opening_quote;
	int		in_quote;

	new_eof = ft_strdup("");
	opening_quote = 0;
	in_quote = 0;
	while (*eof)
	{
		if (!in_quote && (*eof == SQ || *eof == DQ))
		{
			opening_quote = *eof;
			in_quote = 1;
			eof++;
		}
		else if (in_quote && (*eof == opening_quote))
		{
			opening_quote = 0;
			in_quote = 0;
			eof++;
		}
		else
			new_eof = append_str(&eof, new_eof, EXP_DELIMITER, opening_quote);
	}
	return (new_eof);
}
