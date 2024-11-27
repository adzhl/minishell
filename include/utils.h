/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:27:54 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/27 08:56:16 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	**create_env_copy(char **envp);
char	*get_env_value(char **env, const char *name);
int		update_env_value(char **env, const char *name, const char *value);
void	print_exit_error(char *arg, char *message);
int		find_var_name(char **env, const char *name);
int		valid_var_name(const char *name);
void	free_array(char **array);
int		print_sorted_env(char **env);
int		get_env_size(char **env);

#endif