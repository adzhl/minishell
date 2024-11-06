/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:16:29 by etien             #+#    #+#             */
/*   Updated: 2024/11/06 15:27:46 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

// Error messages
# define UNCLOSED_QUOTES "Syntax error: Unclosed quotes."

char	*expand_var(char *s);
void	expansion_control(char **s, char *initial_quote,
			int *in_quote_context, char **expanded_s);

// Util functions
char	*sub_in_var(char **s, char *expanded_s);
char	*append_expansion(char *expanded_s, char *expansion);
char	*append_exit_status(char **s, char *expanded_s);
char	*append_str(char **s, char *expanded_s, char initial_quote);

#endif
