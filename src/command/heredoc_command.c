/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:11:37 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/14 11:47:00 by yoonslee         ###   ########.fr       */
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
	if (!ft_strncmp_all("cat", str) || !ft_strncmp_all("grep", str) \
		|| !ft_strncmp_all("wc", str))
		return (1);
	return (0);
}

int	handle_heredoc(t_command *cmd, int *index, int track, char **input)
{
	int		cmd_index;
	// char	*file_name;
	// char	*number;

	// number = ft_itoa(track);
	// file_name = ft_strjoin("HEREDOC", number);
	cmd_index = 0;
	printf("input[cmd_index]: %s\n", input[cmd_index]);
	printf("index: %d\n", *index);
	if (!ft_strncmp_all("<<", input[(*index)]))
	{
		if ((*index) > 0 && input[(*index) - 1] \
		&& input[(*index) - 1][0] != '|')
			cmd_index = (*index) - 1;
		else if (input[(*index) + 1] && input[(*index) + 2] \
		&& input[(*index) + 2][0] != '|')
			cmd_index = (*index) + 2;
	printf("input[cmd_index]: %s\n", input[cmd_index]);
		if (check_for_cat_grep(input[cmd_index]))
		{
			printf("store here\n");
			cmd[track].infile_name = ft_strdup(HEREDOC);
		}
		// if (!ft_strncmp(input[cmd_index + 1], "-", 1))
		// 	(*index) += 3;
		(*index) += 2;
		return (1);
	}
	return (0);
}
