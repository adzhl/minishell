/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:27:54 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/18 17:35:01 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_mshell	t_mshell;

char					**copy_env(char **envp);
char					*get_env_value(char **env, const char *name);
int						update_env_value(char **env, const char *name,
							const char *value);
int						find_var_name(char **env, const char *name);
int						valid_var_name(const char *name);
void					free_array(char **array);
int						print_sorted_env(char **env);
int						get_env_size(char **env);
int						set_exit_status(t_mshell *shell, int status);
int						get_exit_status(t_mshell *shell);
char					*find_path(char *cmd, t_mshell *shell);
void					cmd_error(char *cmd_path, t_exec_cmd *ecmd);

#endif
