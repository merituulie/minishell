/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:02:18 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/08 13:37:15 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../headers/lexer.h"

void	ft_putstr_fd(char *s, int fd, int print_shellname)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (print_shellname)
		ft_putstr_fd(PINK"PinkShell: "BORING, fd, 0);
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
