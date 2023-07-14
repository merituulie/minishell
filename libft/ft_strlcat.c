/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <vvu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:16:55 by vvu               #+#    #+#             */
/*   Updated: 2023/01/16 15:44:43 by vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_size;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (dstsize == 0)
		return (src_size);
	dest_size = ft_strlen(dst);
	if (dstsize <= dest_size)
		return (src_size + dstsize);
	while (src[i] && (dest_size + i < dstsize - 1))
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[dest_size + i] = '\0';
	return (dest_size + src_size);
}
