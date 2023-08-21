/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:19:09 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/21 16:07:43 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	*allocate_pids(int pid_count)
{
	int	*pids;

	pids = ft_calloc(pid_count, sizeof(*pids));
	if (!pids)
		malloc_error();
	return (pids);
}
