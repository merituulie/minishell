/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:22:33 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/18 16:08:03 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_dup2(int infile_fd, int outfile_fd)
{
	if (dup2(infile_fd, 0) < 0)
		ft_putstr_fd("Dup 2 error!", 2);
	if (dup2(outfile_fd, 1) < 0)
		ft_putstr_fd("Dup 2 error!", 2);
}

static void	execute_child(t_command *current, t_command *next, t_env **env, int *pipe_fds)
{
	if (current->id == 0)
		ft_dup2(current->infile_fd, pipe_fds[1]);
	else if (!next)
		ft_dup2(pipe_fds[0], current->outfile_fd);
	else
		ft_dup2(pipe_fds[0], pipe_fds[1]);
	close_files(pipe_fds,  current);
	execute_command(current, next, env);
	exit(0);
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

int	handle_pipe(t_command *commands, t_env **env)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) < 0)
		ft_putstr_fd("Piping error!", 2);
	open_files(&commands);
	commands->pid = fork();
	if (commands->pid < 0)
		ft_putstr_fd("Forking error!", 2);
	if (commands->pid == 0)
		execute_child(commands, commands + 1, env, pipe_fds);
	return (commands->pid);
}
