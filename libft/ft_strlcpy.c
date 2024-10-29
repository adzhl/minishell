/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:50:12 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:26:57 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy strings with the same input parameters and output result as 
 * snprintf(3). This function take the full size of the destination buffer 
 * and guarantee NUL-termination if there is room. Note that room for the NUL
 * should be included in dstsize. It copies up to dstsize - 1 characters from
 * the string src to dst, NUL-terminating the result if dstsize is not 0.
 @return  The total length of the string they tried to create.
 For strlcpy() that means the length of src.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
