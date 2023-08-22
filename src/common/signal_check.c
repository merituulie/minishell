/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:00:36 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 11:00:38 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	adjust_status(int status)
{
	if (status == 2)
	{
		g_info.sig_status = 2;
		set_exit_code(130);
	}
	else
		set_exit_code(WEXITSTATUS(status));
}
