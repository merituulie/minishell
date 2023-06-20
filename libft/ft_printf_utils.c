/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:48:45 by yoonslee          #+#    #+#             */
/*   Updated: 2023/05/04 13:08:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printnbr(int n)
{
	int		i;
	char	*nbr;

	i = 0;
	nbr = ft_itoa(n);
	i = ft_printstr(nbr);
	free(nbr);
	nbr = NULL;
	return (i);
}

int	ft_printnbr_unsigned(unsigned int n)
{
	int	len;

	len = 1;
	if (n / 10 > 0)
	{
		len += ft_printnbr_unsigned(n / 10);
	}
	n = n % 10;
	if (n < 10 && n >= 0)
	{
		ft_printchr(n + '0');
	}
	return (len);
}
