/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/19 15:30:54 by emeinert         ###   ########.fr       */
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
		return ;
	else
		ft_execve(command, env);
}

int	execute_commands(t_command *commands, int command_count, t_env **env)
{
	int			i;
	int 		pids[command_count];

	i = 0;
	// handle one and only command before forking or whatevs
	while (i < command_count)
	{
		commands->id = i;
		if (i == (command_count - 1))
			pids[i] = handle_pipe(commands, env, 1);
		else
			pids[i] = handle_pipe(commands, env, 0);
		commands++;
		i++;
	}
	wait_children(pids, i);
	return (0);
}
