/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:33:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/03 11:59:53 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		// printf("array in free_array[%i]: %s\tp: %p\n", i, array[i], &(*array));
		if (array[i])
		{
			free (array[i]);
			array[i] = NULL;
		}
		i++;
	}
	if (array)
		free (array);
}
