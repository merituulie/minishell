/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:05:43 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/25 06:41:24 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str;
	char	*dest;

	str = (char *)src;
	dest = (char *)dst;
	if (!str && !dest && n > 0)
		return (NULL);
	while (n-- > 0)
		*(dest++) = *(str++);
	dest = NULL;
	str = NULL;
	return (dst);
}
