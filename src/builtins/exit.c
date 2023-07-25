/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:53:15 by emmameinert       #+#    #+#             */
/*   Updated: 2023/07/25 13:45:48 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_is_number(char **input)
{
	int	i;

	i = 0;
	while (input[0][i] != '\0')
	{
		if (!ft_isdigit(input[0][i]))
			return (0);
		i++;
	}
	return (1);
}

static	int	num_arg_check(char **input, int exit_code)
{
	if (ft_is_number(input))
	{
		exit_code = ft_atoi_exit(input[0]);
		if (exit_code < 0)
			exit_code = exit_code * (-1);
		if (exit_code > 255 || exit_code < 0)
			exit_code = exit_code - 256;
		return (exit_code);
	}
	else
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", input[0]);
		exit_code = 255;
		exit(exit_code);
		return (exit_code);
	}
}

static int	amount_check(char **command)
{
	int	count;

	count = 0;
	while (command[count])
	{
		count++;
	}
	if (count > 1)
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
	int		exit_code;
	char	**splitted;

	exit_code = 0;
	flag = 0;
	if (!command->input)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	splitted = ft_split(command->input, ' ');
	exit_code = num_arg_check(splitted, 0);
	flag = amount_check(splitted);
	free_char_array(splitted);
	if (flag)
		return ;
	else
	{
		printf("exit\n");
		exit(exit_code);
	}
}
