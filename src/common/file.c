/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:36:48 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/14 17:54:38 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_file(char *filename, int flags)
{
	int	fd;

	if (!accessable_for_open(filename, flags))
		return (-1);
	fd = open(filename, flags, S_IRWXU);
	if (fd < 0)
	{
		set_exit_code(1);
		ft_putstr_fd("Error when opening a file.\n", 2, 1);
	}
	return (fd);
}

void	close_file(int fd)
{
	if (fd == 0 || fd == 1 || fd == -1)
		return ;
	if (close(fd) == 0)
		return ;
	ft_putstr_fd("Error when closing a file.\n", 2, 1);
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

/*redir_fd_index_in: for the infile only
redir_fd_index_out: for the outfile only*/
int	open_redirection_file(t_command *current)
{
	int			fd;

	fd = -2;
	printf("current.redir_fd_index_in is %d\n", current->redir_fd_index_in);
	printf("current.redir_fd_index_out is %d\n", current->redir_fd_index_out);
	if (current->token == INPUT)
	{
		printf("came here!\n");
		fd = open_file(current->infile_name, O_RDONLY);
	}
	else if (current->token == OUTPUT_TRUNC)
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_TRUNC);
	else if (current->token == OUTPUT_APPEND)
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_APPEND);
	printf("fd is %d\n", fd);
	if (current->token == INPUT)
	{
		current->redir_fd_index_in = g_info.redir_index_count;
		printf("current.redir_fd_index_in is %d\n", current->redir_fd_index_in);
	}
	else if (current->token == OUTPUT_TRUNC || current->token == OUTPUT_APPEND)
	{
		current->redir_fd_index_out = g_info.redir_index_count;
		printf("current.redir_fd_index_out is %d\n", current->redir_fd_index_out);
	}
	printf("current.token is %d\n", current->token);
	printf("current iterator is %d\n", g_info.redir_index_count);
	g_info.redir_fds[g_info.redir_index_count++] = fd;
	printf("----------after if else---------\n");
	printf("current.redir_fd_index_in is %d\n", current->redir_fd_index_in);
	if (current->redir_fd_index_in != -2)
		printf("current.value is %d\n", g_info.redir_fds[current->redir_fd_index_in]);
	if (current->redir_fd_index_out != -2)
		printf("current.redir_fd_index_out is %d\n",g_info.redir_fds[current->redir_fd_index_out]);
	printf("---------------------------------\n");
	return (fd);
}
