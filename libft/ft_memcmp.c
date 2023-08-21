/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:35:13 by vvu               #+#    #+#             */
/*   Updated: 2023/08/21 09:21:55 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*pt1;
	const unsigned char	*pt2;

	pt1 = s1;
	pt2 = s2;
	if (pt1 && ft_strlen((const char *)pt1) == 0)
		return (1);
	while (n--)
	{
		if (*pt1++ != *pt2++)
			return (*(--pt1) - *(--pt2));
	}
	return (0);
}
