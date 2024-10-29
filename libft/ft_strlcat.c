/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:03:45 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 13:29:45 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Concatenate strings with the same input parameters and output result 
 * as snprintf(3). This function take the full size of the destination buffer 
 * and guarantee NUL-termination if there is room. Note that room for the NUL
 * should be included in dstsize.
 * Strlcat() appends string src to the end of dst.  It will append at most
 * dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
 * dstsize is 0 or the original dst string was longer than dstsize. 
 * If the src and dst strings overlap, the behavior is undefined.
 @return  The total length of the string they tried to create. For strlcat() 
 that means the initial length of dst plus the length of src.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dst == NULL && dstsize == 0)
		return (src_len);
	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len] != '\0')
		dst_len++;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	else
	{
		i = 0;
		while (src[i] != '\0' && dst_len + i < dstsize - 1)
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	return (src_len + dst_len);
}
