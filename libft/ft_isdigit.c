/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:53:55 by emeinert          #+#    #+#             */
/*   Updated: 2023/07/24 11:01:08 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	int	answer;
	printf("c in ft_isgit: %c\n", c);
	answer = 0;
	if (c >= '0' && c <= '9')
		answer = 1;
	else
		answer = 0;
	return (answer);
}
