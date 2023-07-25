/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/25 16:10:03 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	error_code(int number)
{
	g_info.exit_code = number;
}

void	error_msg(char *str, t_command *command)
{
	char	*msg;

	msg = ft_strjoin(BORING "PinkShell: " BORING, command->command);
	if (!msg)
		printf("malloc_error\n");
	msg = ft_strjoin(msg, str);
	ft_putstr_fd(msg, 2);
	error_code(127);
}
