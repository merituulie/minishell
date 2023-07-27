/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:36:48 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/27 14:05:16 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_file(char *filename, int flags)
{
	int fd;

	fd = open(filename, flags, S_IRWXU);
	if (fd < 0)
		ft_putstr_fd("Error in opening a file.\n", 2);
	return (fd);
}

int close_file(int fd)
{
	if (close(fd) != 0)
		ft_putstr_fd("Error when closing a file.\n", 2);
	return (0);
}

void	close_files(int *pipe_fds, int fd_count)
{
	int	i;

	i = 0;
	while (i < fd_count)
	{
		close_file(pipe_fds[i]);
		i++;
	}
}
