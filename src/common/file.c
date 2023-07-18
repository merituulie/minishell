/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:34:22 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/18 16:06:41 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	open_files(t_command **current)
{
	(*current)->infile_fd = open((*current)->infile_name, O_RDWR | O_CREAT, S_IRWXU);
	if ((*current)->infile_fd == -1)
	{
		ft_putstr_fd("Infile error!", 2);
		return ;
	}
	(*current)->outfile_fd = open((*current)->outfile_name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if ((*current)->outfile_fd == -1)
		ft_putstr_fd("Outfile error!", 2);
}

void	close_files(int *pipe_fds, t_command *current)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(current->infile_fd);
	close(current->outfile_fd);
}
