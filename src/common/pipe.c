/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmameinert <emmameinert@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:22:33 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/28 10:40:37 by emmameinert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_dup2(int infile_fd, int outfile_fd)
{
	if (infile_fd != -2 && dup2(infile_fd, 0) < 0)
		ft_putstr_fd("infile_fd:  Dup 2 error!\n", 2);
	if (outfile_fd != -2 && dup2(outfile_fd, 1) < 0)
		ft_putstr_fd("outfile_fd: Dup 2 error!\n", 2);
}

void	close_files(int *pipe_fds, int fd_count)
{
	int	i;

	i = 0;
	while (i < fd_count)
	{
		close(pipe_fds[i]);
		i++;
	}
}

static void	execute_child(t_command *current, int command_count, \
			t_env **env, int *pipe_fds)
{
	if (current->id == 0)
		ft_dup2(-2, pipe_fds[current->id * 2 + 1]);
	else if (current->id == command_count - 1) 
		ft_dup2(pipe_fds[(current->id * 2) - 2], -2);
	else
	{
		ft_dup2(pipe_fds[current->id * 2 - 2], pipe_fds[current->id * 2 + 1]);
	}
	close_files(pipe_fds, command_count * 2 - 2);
	execute_command(current, env, 1);
}

void	wait_children(int *pids, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

int	handle_pipe(t_command *commands, t_env **env, \
			int command_count, int *pipe_fds)
{
	commands->pid = fork();
	if (commands->pid < 0)
		ft_putstr_fd("Forking error!", 2);
	if (commands->pid == 0)
		execute_child(commands, command_count, env, pipe_fds);
	return (commands->pid);
}
