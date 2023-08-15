/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:47:52 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/15 16:58:35 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	cmd_is_not_executable(t_command *command)
{
	int	accessable;

	accessable = access(command->command, F_OK);
	if (accessable == 0)
	{
		if (access(command->command, X_OK) == -1)
		{
			ft_puterror(126, ": permission denied\n", command);
			exit(126);
		}
	}
}

void	set_exit_code(int number)
{
	g_info.exit_code = number;
}

char	*get_exit_code(void)
{
	char	*str;
	int		nbr;

	nbr = g_info.exit_code;
	str = ft_itoa(nbr);
	g_info.exit_code = 0;
	return (str);
}

void	ft_puterror(int code, char *str, t_command *command)
{
	char	*msg;
	char	*temp;

	if ((code == 127 || code == 126) && command)
	{
		temp = ft_strdup(command->command);
		if (!temp)
			ft_putstr_fd("Memory allocation failure!\n", 2, 1);
		msg = ft_strjoin(temp, str);
		free(temp);
	}
	else
		msg = ft_strdup(str);
	if (!msg)
		ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	ft_putstr_fd(msg, 2, 1);
	free(msg);
	set_exit_code(code);
}
