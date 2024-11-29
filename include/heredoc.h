/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:39:29 by etien             #+#    #+#             */
/*   Updated: 2024/11/29 11:49:40 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

// Heredoc functions
char	*handle_heredoc(char **eof, t_mshell *shell);
void	collect_heredoc_input(int pipefd[2], char *eof);
void	read_heredoc_input(char **hd_content, int pipefd_read);

// Delimiter functions
void	check_delimiter(char **eof, bool *expand_hd);
char	*remove_delimiter_quotes(char *eof);

#endif
