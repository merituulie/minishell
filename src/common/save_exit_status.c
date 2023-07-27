/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/27 13:06:57 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	error_code(int number)
{
	g_info.exit_code = number;
}

void	error_msg(int code, char *str, t_command *command)
{
	char	*msg;
	char	*temp;

	if (code == 127)
	{
		msg = ft_strjoin(BORING "PinkShell: " BORING, command->command);
		if (!msg)
		printf("malloc_error\n");
		temp = msg;
		free(msg);
	}
	else
		temp = BORING "PinkShell: " BORING;
	msg = ft_strjoin(temp, str);
	if (!msg)
		printf("malloc_error\n");
	ft_putstr_fd(msg, 2);
	free(msg);
	error_code(code);
}
