/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:01:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/05/04 13:08:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	result;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	else
		dst_len = ft_strlen(dst);
	result = 0;
	if (dstsize > dst_len)
		result = src_len + dst_len;
	else
	{
		result = src_len + dstsize;
		return (result);
	}
	while (*src && (dst_len + 1) < dstsize)
	{
		dst[dst_len] = *src;
		dst_len++;
		src++;
	}
	dst[dst_len] = '\0';
	return (result);
}
