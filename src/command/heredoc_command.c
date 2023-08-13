/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:11:37 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/13 07:56:45 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_command_redir(t_command *command)
{
	int	fd;
	if (command->infile_name && !ft_strncmp_all(command->infile_name, HEREDOC))
	{
		fd = open_file(HEREDOC, O_RDONLY);
		command->token = INPUT;
		command->redir_fd_index_in = g_info.redir_index_count;
		g_info.redir_fds[g_info.redir_index_count++] = fd;
	}
	else
		unlink(HEREDOC);

}

static int	check_for_cat_grep(char *str)
{
	if (!ft_strncmp_all("cat", str) || !ft_strncmp_all("grep", str))
		return (1);
	return (0);
}

int	handle_heredoc(t_command *cmd, int *index, int track, char **input)
{
	int	cmd_index;

	cmd_index = 0;
	if (!ft_strncmp_all("<<", input[(*index)]))
	{
		if ((*index) > 0 && input[(*index) - 1] \
		&& input[(*index) - 1][0] != '|')
			cmd_index = (*index) - 1;
		else if (input[(*index) + 1] && input[(*index) + 2] \
		&& input[(*index) + 2][0] != '|')
			cmd_index = (*index) + 2;
		if (check_for_cat_grep(input[cmd_index]))
			cmd[track].infile_name = ft_strdup(HEREDOC);
		(*index) += 2;
		return (1);
	}
	return (0);
}
