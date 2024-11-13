/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:39:29 by etien             #+#    #+#             */
/*   Updated: 2024/11/13 14:06:31 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*handle_heredoc(char *eof);
void	collect_heredoc_input(int pipefd[2], char *eof);
void	read_heredoc_input(char **hd_content, int pipefd_read);
char	*expand_heredoc(char *heredoc);
int		ft_strcmp(const char *s1, const char *s2);

void	check_delimiter(char **eof, bool *expand_hd);
char	*remove_delimiter_quotes(char *eof);

#endif
