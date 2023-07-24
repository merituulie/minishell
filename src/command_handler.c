/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/22 13:05:14 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	execute_command(t_command *command, t_env **env)
{
	if (ft_strncmp_all(command->command, "env") == 0)
		ft_env(env);
	else if (ft_strncmp_all(command->command, "echo") == 0)
		return ;
	else if (ft_strncmp_all(command->command, "cd") == 0)
		return ;
	else if (ft_strncmp_all(command->command, "pwd") == 0)
		return ;
	else if (ft_strncmp_all(command->command, "export") == 0)
		return ;
	else if (ft_strncmp_all(command->command, "unset") == 0)
		return ;
	else if (ft_strncmp_all(command->command, "exit") == 0)
	{
		ft_exit(command);
		return ;
	}
	else
		ft_execve(command, env);
}

int	execute_commands(t_command *commands, int command_count, t_env **env)
{
	int			i;
	int 		pids[command_count]; //free
	int			pipe_fds[(command_count * 2) - 2]; //free

	i = 0;
	if (command_count == 1)
	{
		execute_command(commands, env);
		return (0);
	}
	while (i < command_count)
	{
		commands->id = i;
		if (i != command_count - 1)
		{
			if (pipe(&pipe_fds[i * 2]) < 0)
				ft_putstr_fd("Piping error!", 2);
		}
		pids[i] = handle_pipe(commands, env, command_count, pipe_fds);
		commands++;
		i++;
	}
	close_files(pipe_fds, command_count * 2 - 2);
	wait_children(pids, i - 1);
	return (0);
}
