/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:44:29 by                   #+#    #+#             */
/*   Updated: 2023/08/08 13:51:20 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	execute_child(t_command *current, int command_count, \
			t_env **env)
{
	if (current->id == 0)
		redirect_io(-2, g_info.pipe_fds[current->id * 2 + 1]);
	else if (current->id == command_count - 1)
		redirect_io(g_info.pipe_fds[(current->id * 2) - 2], -2);
	else
		redirect_io(g_info.pipe_fds[current->id * 2 - 2], \
		g_info.pipe_fds[current->id * 2 + 1]);
	if (current->token != NONE)
		redirect_files(current);
	execute_command(current, env, 1);
}

void	wait_children(int *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i <= count)
	{
		waitpid(pids[i], &status, 0);
		g_info.exit_code = WEXITSTATUS(status);
		i++;
	}
}

int	handle_pipe(t_command *commands, t_env **env, \
			int command_count)
{
	commands->pid = fork();
	if (commands->pid < 0)
		ft_putstr_fd("Forking error!", 2, 1);
	if (commands->pid == 0)
		execute_child(commands, command_count, env);
	return (commands->pid);
}
