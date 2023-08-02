/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:26:21 by rmakinen          #+#    #+#             */
/*   Updated: 2023/08/02 11:46:30 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

void	ft_dup2(int infile_fd, int outfile_fd)
{
	if (infile_fd != -2 && dup2(infile_fd, 0) < 0)
		ft_putstr_fd("infile_fd:  Dup 2 error!\n", 2);
	if (outfile_fd != -2 && dup2(outfile_fd, 1) < 0)
		ft_putstr_fd("outfile_fd: Dup 2 error!\n", 2);
}

void	redirect_io(int infile_fd, int outfile_fd)
{
	ft_dup2(infile_fd, outfile_fd);
	close_files(g_info.pipe_fds, g_info.pipe_count);
}

void	redirect_files(t_command *current)
{
	if (current->token == INPUT)
		ft_dup2(g_info.redir_fds[current->redir_fd_index], -2);
	else if (current->token == OUTPUT_APPEND \
	|| current->token == OUTPUT_TRUNC)
		ft_dup2(-2, g_info.redir_fds[current->redir_fd_index]);
	// close_files(g_info.redir_fds, g_info.redir_count);
}

int	parse_redirection(t_command *cmd, int track, char *str, char *input)
{
	if (!ft_strncmp_all("<", input))
	{
		cmd[track].infile_name = ft_strdup(str);
		if (!cmd[track].infile_name)
			printf("strdup allocation fail 4!\n");
		cmd[track].token = INPUT;
	}
	else if (!ft_strncmp_all(">", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			printf("strdup allocation fail 5 !\n");
		cmd[track].token = OUTPUT_TRUNC;
	}
	else if (!ft_strncmp_all(">>", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			printf("strdup allocation fail 6!\n");
		cmd[track].token = OUTPUT_APPEND;
	}
	return (0);
}
