/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:53:49 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:53:50 by meskelin         ###   ########.fr       */
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
