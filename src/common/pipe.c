/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmameinert <emmameinert@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:22:33 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/26 15:31:53 by emmameinert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	execute_child(t_command *current, int command_count, \
			t_env **env)
{
	if (current->token == NONE)
	{
		if (current->id == 0)
			redirect_io(current, command_count, -2, g_info.fds[current->id * 2 + 1]);
		else if (current->id == command_count - 1) 
			redirect_io(current, command_count, g_info.fds[(current->id * 2) - 2], -2);
		else
			redirect_io(current, command_count, g_info.fds[current->id * 2 - 2], g_info.fds[current->id * 2 + 1]);
	}
	else
	{
		if (current->id == 0)
			redirect_files(current, command_count, -2, g_info.fds[current->id * 2 + 1]);
		else if (current->id == command_count - 1)
			redirect_files(current, command_count, g_info.fds[(current->id * 2) - 2], -2);
		else
			redirect_files(current, command_count, g_info.fds[current->id * 2 - 2], g_info.fds[current->id * 2 + 1]);
	}
	close_files(g_info.fds, command_count * 2 - 2);
	execute_command(current, env);
}

void	wait_children(int *pids, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		if (pids[i] != -2)
			waitpid(pids[i], NULL, 0);
		i++;
	}
}

int	handle_pipe(t_command *commands, t_env **env, \
			int command_count)
{
	if (commands->token == NONE)
	{
		commands->pid = fork();
		if (commands->pid < 0)
			ft_putstr_fd("Forking error!", 2);
		if (commands->pid == 0)
			execute_child(commands, command_count, env);
		return (commands->pid);
	}
	execute_child(commands, command_count, env);
	return (-2);
}
