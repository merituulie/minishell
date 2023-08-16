/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:51 by emeinert          #+#    #+#             */
/*   Updated: 2023/08/15 17:55:56 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_is_number(char **input)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_strlen(input[1]) == 1 && !ft_isdigit(input[1][0]))
		return (0);
	if (input[1][0] == '-' || input[1][0] == '+')
			i++;
	while (input[1][i] != '\0')
	{
		if (!ft_isdigit(input[1][i]))
			return (0);
		i++;
	}
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

static	void	num_arg_check(char **input, int fork, \
						t_command *cmd, t_env *env)
{
	if (ft_is_number(input))
	{
		g_info.exit_code = ft_atoll(input[1]);
		if (g_info.exit_code < 0)
		{
			g_info.exit_code = g_info.exit_code * (-1);
			g_info.exit_code = 256 - g_info.exit_code;
		}
		if (g_info.exit_code > 255)
			g_info.exit_code = g_info.exit_code % 256;
	}
	else
	{
		g_info.exit_code = 255;
		if (!fork)
			ft_putstr_fd("exit\n", 1, 0);
		ft_putstr_fd("exit: ", 2, 1);
		ft_putstr_fd(input[1], 2, 0);
		ft_putstr_fd(": numeric argument required\n", 2, 0);
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
		g_info.exit_code = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(t_command *command, t_env *env, int fork)
{
	int		flag;

	flag = 0;
	if (!command->input && !command->flags)
	{
		if (!fork)
		{
			ft_putstr_fd("exit\n", 1, 0);
			ft_exit_free(command, env);
		}
		exit(g_info.exit_code);
	}
	num_arg_check(command->full_cmd, fork, command, env);
	flag = amount_check(command->full_cmd, fork);
	if (flag)
		return ;
	else
	{
		if (!fork)
			ft_putstr_fd("exit\n", 1, 0);
		ft_exit_free(command, env);
		exit(g_info.exit_code);
	}
}
