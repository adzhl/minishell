/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_var_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:41:11 by abinti-a          #+#    #+#             */
/*   Updated: 2024/11/27 07:56:54 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

/**
 * An environment variable can only start with '_' or alphabet
 * After the first letter there can only be alphabet, digit or '_'
 */
int	valid_var_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (0);
	i = 1;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}
