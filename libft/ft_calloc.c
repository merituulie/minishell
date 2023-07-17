/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:00:30 by meskelin          #+#    #+#             */
/*   Updated: 2022/11/18 12:08:37 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	amount;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	amount = count * size;
	if (amount % size != 0 || amount % count != 0)
		return (NULL);
	ptr = (void *)malloc(sizeof(*ptr) * amount);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, amount);
	return (ptr);
}
