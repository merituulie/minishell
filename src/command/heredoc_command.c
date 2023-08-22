/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_Command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:57:23 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:57:24 by meskelin         ###   ########.fr       */
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
		if (cmd[track].infile_name)
		{
			update_infile_redir_heredoc(cmd, track);
			cmd[track].infile_name = ft_strdup(file_name);
		}
		else
			cmd[track].infile_name = ft_strdup(file_name);
		free(file_name);
		(*index) += 2;
		return (1);
	}
	free(file_name);
	return (0);
}
