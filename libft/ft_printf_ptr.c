/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:42 by yoonslee          #+#    #+#             */
/*   Updated: 2023/05/04 13:08:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ptr_hexa(unsigned long long n)
{
	int	temp;
	int	count;

	count = 1;
	temp = 0;
	if (n / 16 > 0)
	{
		count += ptr_hexa(n / 16);
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

int	ft_printptr(unsigned long long n)
{
	int	len;

	len = 2;
	ft_printchr('0');
	ft_printchr('x');
	len += ptr_hexa(n);
	return (len);
}
