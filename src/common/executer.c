/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:53:29 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:53:31 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	execute_builtin(t_command **command, t_env ***env, int fork)
{
	if (ft_strncmp_all((*command)->command, "env") == 0)
		ft_env((*env), (*command));
	else if (ft_strncmp_all((*command)->command, "echo") == 0)
		ft_echo((*command));
	else if (ft_strncmp_all((*command)->command, "cd") == 0)
		ft_cd((*command), (*env));
	else if (ft_strncmp_all((*command)->command, "pwd") == 0)
		ft_pwd(**env);
	else if (ft_strncmp_all((*command)->command, "export") == 0)
		ft_export((*command)->input, **env);
	else if (ft_strncmp_all((*command)->command, "unset") == 0)
		ft_unset((*command)->input, **env);
	else if (ft_strncmp_all((*command)->command, "exit") == 0)
		ft_exit((*command), **env, fork, 0);
	else
		return (0);
	return (1);
}

void	execute_command(t_command *command, t_env **env, int fork)
{
	if (command && command->command)
	{
		if (command->command[0] == '\0')
		{
			ft_putstr_fd("command not found\n", 2, 1);
			set_exit_code(127);
			if (fork)
				exit (g_info.exit_code);
			return ;
		}
	}
	else if (command && !command->command && \
		(command->infile_name || command->outfile_name))
		exit(0);
	else
		exit(1);
	if (execute_builtin(&command, &env, fork))
	{
		if (!fork)
			return ;
	}
	else
		execute_ft_execve(command, env);
	if (fork)
		exit(0);
}

static int	dont_fork_cmd(t_command *command)
{
	if (ft_strncmp_all(command->command, "cd") == 0)
		return (1);
	else if (ft_strncmp_all(command->command, "export") == 0 && command->input)
		return (1);
	else if (ft_strncmp_all(command->command, "unset") == 0)
		return (1);
	else if (ft_strncmp_all(command->command, "exit") == 0)
		return (1);
	else
		return (0);
}

static	int	exec_one_command(t_command *command, int command_count, t_env **env)
{
	int			pid_test;
	int			status;

	if (command_count == 1)
	{
		if (dont_fork_cmd(command))
			execute_command(command, env, 0);
		else
		{
			pid_test = fork();
			if (pid_test == 0)
			{
				redirect_files(command);
				execute_command(command, env, 1);
			}	
			waitpid(pid_test, &status, 0);
			adjust_status(status);
		}
		return (1);
	}
	return (0);
}

void	execute_commands(t_command *commands, int command_count, t_env **env)
{
	int	i;
	int	*pids;

	if (exec_one_command(commands, command_count, env))
		return ;
	i = -1;
	pids = allocate_pids(command_count);
	while (command_count != 1 && ++i < command_count)
	{
		commands->id = i;
		if (i != command_count - 1)
		{
			if (pipe(&g_info.pipe_fds[i * 2]) < 0)
				ft_putstr_fd("Piping error!", 2, 1);
		}
		pids[i] = handle_pipe(commands, env, command_count);
		commands++;
	}
	close_files(g_info.pipe_fds, g_info.pipe_count);
	wait_children(pids, i - 1);
	free(pids);
}
