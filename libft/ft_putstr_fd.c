/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:52:01 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 14:40:27 by meskelin         ###   ########.fr       */
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
		ft_putstr_fd(PURPLE"minishell: "BORING, fd, 0);
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
