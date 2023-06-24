/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:06:00 by jhusso            #+#    #+#             */
/*   Updated: 2022/11/11 16:30:09 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;

	slen = ft_strlen(src);
	if (!dstsize)
		return (slen);
	while (dstsize - 1 > 0 && *src)
	{
		*dst = *(char *)src;
		dst++;
		src++;
		dstsize--;
	}
	*dst = '\0';
	return (slen);
}
