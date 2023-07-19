/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:22:33 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/19 15:30:42 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_dup2(int infile_fd, int outfile_fd)
{
	if (infile_fd != -2 && dup2(infile_fd, 0) < 0)
		ft_putstr_fd("Dup 2 error!", 2);
	if (outfile_fd != -2 && dup2(outfile_fd, 1) < 0)
		ft_putstr_fd("Dup 2 error!", 2);
}

void	close_files(int *pipe_fds)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

static void	execute_child(t_command *current, int last, t_env **env, int *pipe_fds)
{
	if (current->id == 0)
		ft_dup2(-2, pipe_fds[1]);
	else if (last)
		ft_dup2(pipe_fds[0], -2);
	else
		ft_dup2(pipe_fds[0], pipe_fds[1]);
	close_files(pipe_fds);
	execute_command(current, env);
	printf("%i exiting!\n", getpid());
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

int	handle_pipe(t_command *commands, t_env **env, int last)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) < 0)
		ft_putstr_fd("Piping error!", 2);
	commands->pid = fork();
	if (commands->pid < 0)
		ft_putstr_fd("Forking error!", 2);
	if (commands->pid == 0)
		execute_child(commands, last, env, pipe_fds);
	return (commands->pid);
}
