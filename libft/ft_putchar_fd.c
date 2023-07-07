/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/07 12:05:43 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/minishell.h"
#include "./headers/hashmap.h"
#include "./libft/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
