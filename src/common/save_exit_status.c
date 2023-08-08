/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/08 13:55:12 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	error_code(int number)
{
	g_info.exit_code = number;
}

char	*get_exit_value(void)
{
	char	*str;
	int		nbr;

	nbr = g_info.exit_code;
	str = ft_itoa(nbr);
	g_info.exit_code = 0;
	return (str);
}

void	error_msg(int code, char *str, t_command *command)
{
	char	*msg;
	char	*temp;

	if (code == 127 || code == 126)
	{
		temp = ft_strdup(command->command);
		if (!temp)
			ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	}
	msg = ft_strjoin(temp, str);
	if (!msg)
		ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	free(temp);
	ft_putstr_fd(msg, 2, 1);
	free(msg);
	g_info.exit_code = code;
}
