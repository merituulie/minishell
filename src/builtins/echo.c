/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:25:17 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/28 08:56:11 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

/*
-takes in an array of strings, each index is a string from the command line.
-if the first string is "-n" echo adds a newline at the end of the last string.
-echo returns 0 if successfull and 1 if not.
*/

int	ft_echo(t_command *command)
{
	int	new_line;

	new_line = 0;
	if (command->flags)
	{
		if (ft_strncmp_all(command->flags, "-n") == 0)
			new_line = 1;
		else
		{
			ft_putstr_fd(command->flags, 2);
			ft_putchar_fd(' ', 2);
		}
	}
	ft_putstr_fd(command->input, 2);
	if (new_line == 0)
		ft_putchar_fd('\n', 2);
	g_info.exit_code = 0;
	return (0);
}
