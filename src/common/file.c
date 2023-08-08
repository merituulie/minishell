/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:36:48 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/08 15:32:59 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	accessable_for_write(char *path, int accessable)
{
	if (accessable != 0)
		return (1);
	accessable = access(path, W_OK);
	if (accessable != 0)
	{
		ft_putstr_fd("file: Permission denied.\n", 2, 1);
		return (0);
	}
	return (1);
}

static int	accessable_for_read(char *path, int accessable)
{
	if (accessable != 0)
	{
		ft_puterror(1, "file: No such file or directory.\n", NULL);
		return (0);
	}
	accessable = access(path, R_OK);
	if (accessable != 0)
	{
		ft_puterror(1, "file: Permission denied.\n", NULL);
		return (0);
	}
	return (1);
}

static int	accessable_for_open(char *filename, int flags)
{
	char	*path;
	int		accessable;

	path = ft_strjoin("./", filename);
	accessable = access(path, F_OK);
	if (flags == O_RDONLY)
		return accessable_for_read(path, accessable);
	else if (flags >= O_WRONLY)
		return accessable_for_write(path, accessable);
	return (1);
}

int	open_file(char *filename, int flags)
{
	int	fd;

	if (!accessable_for_open(filename, flags))
		return (-1);
	fd = open(filename, flags, S_IRWXU);
	if (fd < 0)
		ft_puterror(1, "Error when opening a file.\n", NULL);
	return (fd);
}

int	close_file(int fd)
{
	if (fd == 0 || fd == 1 || fd == -1)
		return (0);
	if (close(fd) == 0)
		return (0);
	ft_putstr_fd("Error when closing a file.\n", 2, 1);
	return (-1);
}

void	close_files(int *pipe_fds, int fd_count)
{
	int	i;

	i = 0;
	while (i < fd_count)
	{
		if (pipe_fds[i])
			close_file(pipe_fds[i]);
		i++;
	}
}

/*redir_fd_index_in: for the infile only
redir_fd_index_out: for the outfile only*/
int	open_redirection_file(t_command *current)
{
	int			fd;

	fd = -2;
	if (current->token == INPUT)
		fd = open_file(current->infile_name, O_RDONLY);
	else if (current->token == OUTPUT_TRUNC)
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_TRUNC);
	else if (current->token == OUTPUT_APPEND)
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_APPEND);
	if (current ->redir_fd_index_in == -2 && (current->token == INPUT))
		current->redir_fd_index_in = g_info.redir_index_count;
	else
		current->redir_fd_index_out = g_info.redir_index_count;
	g_info.redir_fds[g_info.redir_index_count++] = fd;
	return (fd);
}
