/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/31 13:34:25 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_shlvl(t_env **env)
{
	t_node	*temp;
	int		shlvl;

	temp = get_value((*env)->vars, "SHLVL");
	shlvl = ft_atoi_exit(temp->value);
	temp->value = ft_itoa(shlvl + 1);
}

int	execute_builtin(t_command **command, t_env ***env)
{
	if (ft_strncmp_all((*command)->command, "env") == 0)
		ft_env((*env));
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
		ft_exit((*command));
	else if (ft_strncmp_all((*command)->command, "<<") == 0)
		ft_heredoc((*command), (*env));
	else
		return (0);
	return (1);
}

void	execute_command(t_command *command, t_env **env, int fork)
{
	if (execute_builtin(&command, &env))
	{
		if (!fork)
			return ;
	}
	else if (ft_strncmp_all(command->command, "./minishell") == 0)
	{
		add_shlvl(env);
		return ;
	}
	else
	{
		if (ft_execve(command, env) == -1)
		{
			error_msg(127, ": command not found\n", command);
			exit(127);
		}
	}
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

	pid_test = 0;
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
				close_files(g_info.redir_fds, g_info.redir_count);
				execute_command(command, env, 1);
			}
			waitpid(pid_test, &status, 0);
			g_info.exit_code = WEXITSTATUS(status);
			return (1);
		}
		return (1);
	}
	return (0);
}

int	execute_commands(t_command *commands, int command_count, t_env **env)
{
	int			i;
	int			pids[command_count];

	i = -1;
	if (exec_one_command(commands, command_count, env))
	{
		close_files(g_info.redir_fds, g_info.redir_count);
		return (0);
	}
	while (++i < command_count)
	{
		commands->id = i;
		if (i != command_count - 1)
		{
			if (pipe(&g_info.pipe_fds[i * 2]) < 0)
				ft_putstr_fd("Piping error!", 2);
		}
		pids[i] = handle_pipe(commands, env, command_count);
		commands++;
	}
	close_files(g_info.pipe_fds, g_info.pipe_count);
	wait_children(pids, i - 1);
	return (0);
}
