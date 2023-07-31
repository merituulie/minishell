/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmameinert <emmameinert@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:53:15 by emmameinert       #+#    #+#             */
/*   Updated: 2023/07/30 15:01:19 by emmameinert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_is_number(char **input)
{
	int	i;

	i = 0;
	if (ft_strlen(input[1]) == 1 && !ft_isdigit(input[1][0]))
		return (0);
	if(input[1][0] == '-' || input[1][0] == '+')
			i++;
	while (input[1][i] != ' ' && input[1][i] != '\0')
	{
		if (!ft_isdigit(input[1][i]))
			return (0);
		i++;
	}
	return (1);
}

static	void	num_arg_check(char **input)
{
	if (ft_is_number(input))
	{
		g_info.exit_code = ft_atoi_exit(input[1]);
		if (g_info.exit_code < 0)
		{
			g_info.exit_code = g_info.exit_code * (-1);
			g_info.exit_code = 256 - g_info.exit_code;
		}
		if (g_info.exit_code > 255)
			g_info.exit_code = g_info.exit_code - 256;
	}
	else
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", input[1]);
		g_info.exit_code = 255;
		exit(g_info.exit_code);
	}
}

static int	amount_check(char **command)
{
	int	count;

	count = 0;
	while (command[1][count])
	{
		count++;
	}
	if (count > 2)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

void	ft_exit(t_command *command)
{
	int		flag;

	flag = 0;
	if (!command->input && !command->flags)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	num_arg_check(command->full_cmd);
	flag = amount_check(command->full_cmd);
	if (flag)
		return ;
	else
	{
		printf("exit\n");
		exit(g_info.exit_code);
	}
}
