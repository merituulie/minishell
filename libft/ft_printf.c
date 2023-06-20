/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:07:28 by yoonslee          #+#    #+#             */
/*   Updated: 2023/05/04 13:08:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchr(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_check(char c, va_list ap)
{
	int	length;

	length = 0;
	if (c == 'c')
		length += ft_printchr(va_arg(ap, int));
	else if (c == 's')
		length += ft_printstr(va_arg(ap, char *));
	else if (c == 'p')
		length += ft_printptr(va_arg(ap, unsigned long long));
	else if (c == 'd' || c == 'i')
		length += ft_printnbr(va_arg(ap, int));
	else if (c == 'u')
		length += ft_printnbr_unsigned(va_arg(ap, unsigned long));
	else if (c == 'x')
		length += ft_printhex_small(va_arg(ap, unsigned long));
	else if (c == 'X')
		length += ft_printhex_big(va_arg(ap, unsigned long));
	else if (c == '%')
		length += ft_printchr('%');
	return (length);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		length;
	va_list	ap;

	if (!str)
		return (0);
	length = 0;
	va_start(ap, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			length += ft_check(str[i], ap);
		}
		else
			length += ft_printchr(str[i]);
		i++;
	}
	va_end(ap);
	return (length);
}
