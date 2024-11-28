/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:16:29 by etien             #+#    #+#             */
/*   Updated: 2024/11/28 21:55:36 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

// Single quotes
# define SQ '\''
// Double quotes
# define DQ '\"'

// Expansion modes for append_str function
typedef enum expansion_mode
{
	EXP_ARGUMENT,
	EXP_DELIMITER,
	EXP_HEREDOC
}	t_expansion_mode;

// Expansion functions
char	*expand_argument(char *s);
void	expansion_control(char **s, char *opening_quote,
			int *in_quote, char **expanded_s);
char	*expand_heredoc(char *heredoc);

// Expansion util functions
char	*sub_in_var(char **s, char *expanded_s);
char	*append_expansion(char *expanded_s, char *expansion);
char	*append_exit_status(char **s, char *expanded_s);
bool	quotes_are_closed(char *s);

// Append util functions
char	*append_str(char **s, char *expanded_s, int mode, char opening_quote);
char	*append_for_argument(char **s, char opening_quote);
char	*append_for_delimiter(char **s, char opening_quote);
char	*append_for_heredoc(char **s);

#endif
