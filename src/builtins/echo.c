/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:56:24 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:56:26 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_echo(t_command *command)
{
	int	new_line;

	new_line = 0;
	if (command->flags)
	{
		if (ft_strncmp_all(command->flags, "-n") == 0)
			new_line = 1;
		else
		{
			ft_putstr_fd(command->flags, 1, 0);
			ft_putchar_fd(' ', 1);
		}
	}
	if (ft_strncmp_all(command->flags, "-n") && !command->input)
		ft_putchar_fd('\n', 1);
	if (command->input)
	{
		ft_putstr_fd(command->input[0], 1, 0);
		if (new_line == 0)
			ft_putchar_fd('\n', 1);
	}
	set_exit_code(0);
}
