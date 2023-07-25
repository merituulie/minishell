/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/25 14:22:52 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../headers/minishell.h"

void	execute_command(t_command *command, t_env **env)
{
	if (ft_strncmp_all(command->command, "env") == 0)
		ft_env(env);
	else if (ft_strncmp_all(command->command, "echo") == 0)
		ft_echo(command);
	else if (ft_strncmp_all(command->command, "cd") == 0)
		ft_cd(command, env);
	else if (ft_strncmp_all(command->command, "pwd") == 0)
		ft_pwd(*env);
	else if (ft_strncmp_all(command->command, "export") == 0)
		ft_export(command->input, *env);
	else if (ft_strncmp_all(command->command, "unset") == 0)
		ft_unset(command->input, *env);
	else if (ft_strncmp_all(command->command, "exit") == 0)
		ft_exit(command);
	else if (ft_strncmp_all(command->command, "<<") == 0)
		ft_heredoc(command);
	else
	{
		if (ft_execve(command, env) == -1)
			error_msg(": command not found\n", command, env);
	}
	exit(0);
}

int	execute_commands(t_command *commands, int command_count, t_env **env)
{
	int			i;
	int			pids[command_count];
	int			pipe_fds[(command_count * 2) - 2];

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
