/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:36:48 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/30 13:34:48 by rmakinen         ###   ########.fr       */
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
void	open_redirection_file(t_command *current)
{
	static int	index;
	int			fd;

	fd = -2;
	if (current->token == INPUT)
		fd = open_file(current->infile_name, O_RDONLY);
	else if (current->token == OUTPUT_TRUNC)
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_TRUNC);
	else if (current->token == OUTPUT_APPEND)
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_APPEND);
	current->redir_fd_index = index;
	g_info.redir_fds[index++] = fd;
}
