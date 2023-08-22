/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:57:36 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:57:37 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*parse_redirection_filename(char **input, int index)
{
	int		str_len;
	int		cur_index;
	char	*str;

	str_len = 0;
	cur_index = index;
	if (ft_strchr_null("<|>", input[index][0]))
		return (NULL);
	str_len += ft_strlen(input[index]);
	(index)++;
	str = ft_calloc((str_len + 1), sizeof(char));
	if (!str)
		malloc_error();
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	return (str);
}

void	update_infile_redir_heredoc(t_command *cmd, int track)
{
	free(cmd[track].infile_name);
	cmd[track].infile_name = NULL;
	close_file(g_info.redir_fds[cmd->redir_fd_index_in]);
	g_info.redir_fds[cmd->redir_fd_index_in] = -1;
	cmd->redir_fd_index_in = -2;
}

static void	reset_redir_file(t_command *cmd, char **input,	\
											int *index, int track)
{
	if (!(ft_strncmp(input[(*index)], "<", 1)) && cmd[track].infile_name)
		update_infile_redir_heredoc(cmd, track);
	else if (!(ft_strncmp(input[(*index)], ">", 1)) && cmd[track].outfile_name)
	{
		free(cmd[track].outfile_name);
		cmd[track].outfile_name = NULL;
		close_file(g_info.redir_fds[cmd->redir_fd_index_out]);
		g_info.redir_fds[cmd->redir_fd_index_out] = -1;
		cmd->redir_fd_index_out = -2;
	}
}

static int	handle_redirection(t_command *cmd, int *index, \
		int track, char **input)
{
	char	*str;

	str = NULL;
	while (ft_strchr_null("<>", input[(*index)][0]) \
	&& ft_strncmp_all("<<", input[(*index)]))
	{
		reset_redir_file(cmd, input, index, track);
		str = parse_redirection_filename(input, (*index + 1));
		parse_redirection(cmd, track, str, input[(*index)]);
		if (str)
			free(str);
		if (open_redirection_file(&cmd[track]) < 0)
		{
			clear_failed_redir(&cmd[track]);
			return (-1);
		}
		(*index) += 2;
		if (!input[*index])
			break ;
	}
	return (0);
}

int	check_null_index_handle_redirs(t_command *cmd, int track, \
	char **input, int *index)
{
	if (!input[(*index)])
		return (-1);
	if (handle_redirection(cmd, index, track, input) == -1)
	{
		while (input[(*index)] && !ft_strchr("|", input[(*index)][0]))
			(*index)++;
	}
	if (!input[(*index)])
		return (-1);
	return (0);
}
