/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:53:15 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:53:17 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	malloc_error(void)
{
	ft_putstr_fd("Memory allocation failed\n", 2, 1);
	exit(1);
}
