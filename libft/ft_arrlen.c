/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmameinert <emmameinert@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:25:23 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/27 11:17:56 by emmameinert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrlen(char **array)
{
	int	counter;

	counter = 0;
	while (*array)
	{
		counter++;
		array++;
	}
	return (counter);
}
