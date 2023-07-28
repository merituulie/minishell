/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:50:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/28 08:46:12 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	error_code(int number)
{
	g_info.exit_code = number;
	// printf("g_info.exit_code is %d\n", g_info.exit_code);
}

char	*get_exit_value(void)
{
	char	*str;
	int		nbr;

	nbr = g_info.exit_code;
	str = ft_itoa(nbr);
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
