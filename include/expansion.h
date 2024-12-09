/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:16:29 by etien             #+#    #+#             */
/*   Updated: 2024/12/09 20:33:48 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

// Single quotes
# define SQ '\''
// Double quotes
# define DQ '\"'

// Quote type for toggle_quotes function
# define OPENING_QUOTE 1
# define CLOSING_QUOTE 2

// Expansion modes for append_str function
typedef enum expansion_mode
{
	EXP_ARGUMENT,
	EXP_DELIMITER,
	EXP_HEREDOC
}	t_expansion_mode;

// Expansion functions
char	*expand_argument(char *s, t_mshell *shell);
void	toggle_quotes(char **s, char *opening_quote, int *in_quote, int quote);
void	expand_argv(char **argv, t_mshell *shell);
char	*expand_heredoc(char *heredoc, t_mshell *shell);

// Expansion util functions
char	*sub_in_var(char **s, char *expanded_s, t_mshell *shell);
char	*append_expansion(char *expanded_s, char *expansion);
char	*append_exit_status(char **s, char *expanded_s, t_mshell *shell);
bool	quotes_are_closed(char *s);

// Append util functions
char	*append_str(char **s, char *expanded_s, int mode, char opening_quote);
char	*append_for_argument(char **s, char opening_quote);
char	*append_for_delimiter(char **s, char opening_quote);
char	*append_for_heredoc(char **s);

#endif
