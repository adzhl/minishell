/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:20:45 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:41:41 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The toupper() function converts a lower-case letter to the 
 * corresponding upper-case letter.
 * @return If the argument is a lower-case letter, the toupper() function 
 * returns the corresponding upper-case letter if there is one; otherwise, 
 * the argument is returned unchanged.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c + ('A' - 'a');
	return (c);
}
