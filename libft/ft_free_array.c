/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:33:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/04 10:12:26 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("in free array getting freed: array[%i]: %s p: %p\n", i, array[i], &(*array[i]));
		free (array[i]);
		i++;
	}
	free (array);
}
