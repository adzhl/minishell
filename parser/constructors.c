/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:21 by etien             #+#    #+#             */
/*   Updated: 2024/10/29 11:45:40 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

// This file contains the constructor functions for the various nodes
// that will be used to construct the parsing tree.
// The general flow of each function is as follows:
// - malloc the node
// - call memset as an initialization measure to prevent undefined behaviour
// - fill in the fields in the node with parameters passed in to
//   the constructor function

// Constructor for execcmd node
t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));

}

// Constructor for redircmd node
t_cmd	*redircmd()
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(t_redircmd));
}

// Constructor for pipecmd node
t_cmd	*pipecmd()
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(t_pipecmd));
}
