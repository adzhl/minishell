/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:56:35 by etien             #+#    #+#             */
/*   Updated: 2024/11/18 10:56:47 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This function will print an error message to STDERR and exit the program.
void error_and_exit(char *err_msg)
{
	ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
