/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:56:33 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:56:34 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_is_number(char **input)
{
	int		i;
	char	*temp;

	i = -1;
	if (ft_strlen(input[1]) == 1 && !ft_isdigit(input[1][0]))
		return (0);
	if (input[1][0] == '-' || input[1][0] == '+')
			i++;
	while (input[1][++i] != '\0')
	{
		if (!ft_isdigit(input[1][i]))
			return (0);
	}
	if (i < 19)
		return (1);
	temp = ft_lltoa(ft_atoll(input[1]));
	if (ft_strncmp_all(input[1], temp) \
	|| (i > 20 && input[1][0] == '-' && input[1][0] == '+') \
	|| (i > 19 && input[1][0] != '-' && input[1][0] != '+'))
	{
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

static void	ft_exit_free(t_command *cmd, t_env *env)
{
	clear_hashmap(env->vars);
	free_in_minishell(cmd, g_info.pipe_count + 1);
}

static void	num_arg_check(char **input, int fork, \
						t_command *cmd, t_env *env)
{
	long long	exit_value;

	if (ft_is_number(input))
	{
		exit_value = ft_atoll(input[1]);
		if (exit_value < 0)
		{
			exit_value = exit_value * (-1);
			g_info.exit_code = 256 - (exit_value % 256);
		}
		else if (exit_value > 255)
			g_info.exit_code = exit_value % 256;
		else
			g_info.exit_code = exit_value;
	}
	else
	{
		set_exit_code(255);
		if (!fork)
			ft_putstr_fd("exit\n", 1, 0);
		exp_unset_exit_msg(input[1], 2);
		ft_exit_free(cmd, env);
		exit(g_info.exit_code);
	}
}

static int	amount_check(char **input, int fork)
{
	int	count;

	count = 0;
	while (input[count])
	{
		count++;
	}
	if (count > 2)
	{
		if (!fork)
			ft_putstr_fd("exit\n", 1, 0);
		ft_putstr_fd("exit: too many arguments\n", 2, 1);
		set_exit_code(1);
		return (1);
	}
	return (0);
}

void	ft_exit(t_command *command, t_env *env, int fork, int flag)
{
	if (!command->input && !command->flags)
	{
		if (!fork)
		{
			ft_putstr_fd("exit\n", 1, 0);
			ft_exit_free(command, env);
			exit(g_info.exit_code);
		}
		set_exit_code(0);
		exit(g_info.exit_code);
	}
	num_arg_check(command->full_cmd, fork, command, env);
	flag = amount_check(command->full_cmd, fork);
	if (flag)
		return ;
	else
	{
		if (!fork)
		{
			ft_exit_free(command, env);
			ft_putstr_fd("exit\n", 1, 0);
		}
		exit(g_info.exit_code);
	}
}
