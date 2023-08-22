/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:53 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:50:58 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_intlen(int nb)
{
	long	len;

	len = 0;
	if (nb == 0)
		len = 1;
	else
	{
		while (nb != 0)
		{
			nb = nb / 10;
			len++;
		}
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	len;
	char	*str;
	long	nb;

	nb = (long)n;
	len = ft_intlen(nb);
	if (nb < 0)
	{
		nb = -1 * nb;
		len += 1;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		malloc_error();
	str[len] = '\0';
	while (len--)
	{
	str[len] = (nb % 10) + '0';
	nb = nb / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
