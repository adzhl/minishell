/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:39:29 by etien             #+#    #+#             */
/*   Updated: 2024/11/11 16:39:53 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

void	handle_heredoc(char *delimiter);
void	collect_hd_input(int pipefd[2], char *delimiter);
void	read_hd_input(char **hd_content, int pipefd_read);
int		ft_strcmp(const char *s1, const char *s2);

#endif
