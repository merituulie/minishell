/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:19:09 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/15 11:24:25 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	*allocate_pids(int pid_count)
{
	int	*pids;

	pids = ft_calloc(pid_count, sizeof(*pids));
	if (!pids)
		ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	return (pids);
}
