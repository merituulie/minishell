/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:40:14 by yoonslee          #+#    #+#             */
/*   Updated: 2023/05/04 13:08:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex_big(unsigned int n)
{
	int	temp;
	int	count;

	count = 1;
	temp = 0;
	if (n / 16 > 0)
		count += ft_printhex_big(n / 16);
	n = n % 16;
	if (n > 9 && n <= 15)
		temp = n - 10 + 'a';
	if (n >= 0 && n <= 9)
		temp = n + '0';
	ft_printchr(temp);
	return (count);
}

int	ft_printhex_small(unsigned int n)
{
	int	temp;
	int	count;

	count = 1;
	temp = 0;
	if (n / 16 > 0)
	{
		count += ft_printhex_small(n / 16);
	}
	n = n % 16;
	if (n >= 0 && n <= 15)
	{
		if (n > 9 && n <= 15)
			temp = n - 10 + 'a';
		else
			temp = n + '0';
	}
	ft_printchr(temp);
	return (count);
}
