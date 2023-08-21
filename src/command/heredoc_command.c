/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:11:37 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/21 08:43:02 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_command_redir(t_command *command)
{
	int	fd;

	if (command->infile_name && !ft_strncmp(command->infile_name, "HEREDOC", 7))
	{
		fd = open_file(command->infile_name, O_RDONLY);
		command->token = INPUT;
		command->redir_fd_index_in = g_info.redir_index_count;
		g_info.redir_fds[g_info.redir_index_count++] = fd;
		unlink(command->infile_name);
	}
}

int	handle_heredoc(t_command *cmd, int *index, int track, char **input)
{
	char	*file_name;
	char	*number;

	number = ft_itoa(track);
	file_name = ft_strjoin("HEREDOC", number);
	free(number);
	if (!ft_strncmp_all("<<", input[(*index)]))
	{
		cmd[track].infile_name = ft_strdup(file_name);
		if (cmd[track].infile_name && \
			ft_strncmp(cmd[track].infile_name, "HEREDOC", 7))
		{
			update_infile_redir_heredoc(cmd, track);
			cmd[track].infile_name = ft_strdup(file_name);
		}
		free(file_name);
		(*index) += 2;
		return (1);
	}
	free(file_name);
	return (0);
}
