/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:57:16 by meskelin          #+#    #+#             */
/*   Updated: 2022/11/15 19:58:07 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize)
	{
		if (src_len >= dstsize)
		{
			len = dstsize - 1;
		}
		else
		{
			len = src_len;
		}
		ft_memcpy((char *)dst, (char *)src, len);
		dst[len] = '\0';
	}
	return (src_len);
}
