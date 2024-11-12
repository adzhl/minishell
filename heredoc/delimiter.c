/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:04:12 by etien             #+#    #+#             */
/*   Updated: 2024/11/12 13:47:14 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will check the delimiter for closed quotes.
// If there are quotes, they will be removed and expand_hd will
// be set to false to prevent heredoc expansion.
// Irregardless of quotes, the function will assign a dynamically-allocated
// string to the delimiter.
void check_delimiter(char **delimiter, bool *expand_hd)
{
	// if (!has_quotes(delimiter))
	// {
	// 	*delimiter = ft_strdup(*delimiter);
	// 	return ;
	// }
	*delimiter = remove_quotes(*delimiter);
	*expand_hd = false;
}

// This function will remove the quotes from the delimiter so that the
// EOF will be correctly detected by the collect_hd_input function.
// The delimiter is modified by literal expansion only.
char	*remove_quotes(char *delimiter)
{
	char	*new_delimiter;
	char	opening_quote;
	int		in_quote;

	new_delimiter = ft_strdup("");
	opening_quote = '\0';
	in_quote = 0;
	while (*delimiter)
	{
		if (!in_quote && (*delimiter == '\'' || *delimiter == '\"'))
		{
			opening_quote = *delimiter;
			in_quote = 1;
			delimiter++;
		}
		else if (in_quote && (*delimiter == '\'' || *delimiter == '\"'))
		{
			opening_quote = *delimiter;
			in_quote = 1;
			delimiter++;
		}
		else
			new_delimiter = append_str(&delimiter, new_delimiter, DELIMITER, opening_quote);
	}
	return (new_delimiter);
}
