/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:26:21 by rmakinen          #+#    #+#             */
/*   Updated: 2023/08/08 13:51:55 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

void	ft_dup2(int infile_fd, int outfile_fd)
{
	if (infile_fd != -2 && dup2(infile_fd, 0) < 0)
		ft_putstr_fd("Redirecting stdin:  Dup 2 error!\n", 2, 1);
	if (outfile_fd != -2 && dup2(outfile_fd, 1) < 0)
		ft_putstr_fd("Redirecting stdout: Dup 2 error!\n", 2, 1);
}

void	redirect_io(int infile_fd, int outfile_fd)
{
	ft_dup2(infile_fd, outfile_fd);
	close_files(g_info.pipe_fds, g_info.pipe_count);
}

/*checks if index is -2, if opening infile fails(without pipe)
checks if g_info.redir_fds[current->redir_fd_index_in] is -1,
opening infile fails(with pipe)*/
void	redirect_files(t_command *current)
{
	if (current->redir_fd_index_in != -2 \
		&& g_info.redir_fds[current->redir_fd_index_in] != -1)
		ft_dup2(g_info.redir_fds[current->redir_fd_index_in], -2);
	if (current->redir_fd_index_out != -2 \
		&& g_info.redir_fds[current->redir_fd_index_out] != -1)
		ft_dup2(-2, g_info.redir_fds[current->redir_fd_index_out]);
	close_files(g_info.redir_fds, g_info.redir_count);
}

int	parse_redirection(t_command *cmd, int track, char *str, char *input)
{
	if (!ft_strncmp_all("<", input))
	{
		cmd[track].infile_name = ft_strdup(str);
		if (!cmd[track].infile_name)
			ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
		cmd[track].token = INPUT;
	}
	else if (!ft_strncmp_all(">", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
		cmd[track].token = OUTPUT_TRUNC;
	}
	else if (!ft_strncmp_all(">>", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
		cmd[track].token = OUTPUT_APPEND;
	}
	return (0);
}

void	clear_failed_redir(t_command *cmd)
{
	if (cmd->command)
		free_and_nullify(cmd->command);
	if (cmd->flags)
		free_and_nullify(cmd->flags);
	if (cmd->input)
		free_char_array(cmd->input);
	if (cmd->infile_name)
		free_and_nullify(cmd->infile_name);
	if (cmd->outfile_name)
		free_and_nullify(cmd->outfile_name);
	cmd->redir_fd_index_in = -2;
	cmd->redir_fd_index_out = -2;
	if (cmd->token)
		cmd->token = NONE;
}
