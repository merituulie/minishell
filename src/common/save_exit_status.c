/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/02 15:22:23 by jhusso           ###   ########.fr       */
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

	if (code == 127)
	{
		temp = ft_strjoin("PinkShell: ", command->command);
		if (!temp)
			printf("malloc_error\n");
	}
	else
	{
		temp = ft_strdup("PinkShell: ");
		if (!temp)
			printf("malloc_error\n");
	}
	msg = ft_strjoin(temp, str);
	if (!msg)
		printf("malloc_error\n");
	free(temp);
	ft_putstr_fd(msg, 2);
	free(msg);
	g_info.exit_code = code;
}
