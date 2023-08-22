/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:57:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:57:29 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	count_struct(char **input)
{
	int	struct_count;
	int	index;

	struct_count = 0;
	index = 0;
	while (input[index])
	{
		if (input[index][0] == '|')
			struct_count++;
		index++;
	}
	struct_count++;
	return (struct_count);
}

static int	count_redirs(char **input)
{
	int	redir_count;
	int	index;

	redir_count = 0;
	index = 0;
	while (input[index])
	{
		if (ft_strchr_null("<>", input[index][0]))
			redir_count++;
		index++;
	}
	return (redir_count);
}

static void	init_fds_count_redirs(int *struct_count, char **input)
{
	g_info.redir_index_count = 0;
	g_info.pipe_count = (*struct_count) * 2 - 2;
	if (g_info.pipe_count > 0)
	{
		g_info.pipe_fds = ft_calloc(g_info.pipe_count, sizeof(g_info.pipe_fds));
		if (!g_info.pipe_fds)
			malloc_error();
	}
	g_info.redir_count = count_redirs(input);
	if (g_info.redir_count > 0)
	{
		g_info.redir_fds = ft_calloc(g_info.redir_count, \
		sizeof(g_info.redir_fds));
		if (!g_info.redir_fds)
			malloc_error();
	}
}

t_command	*init_cmds(t_data *ms, char **input)
{
	t_command	*cmd;
	int			track;

	track = 0;
	ms->struct_count = count_struct(input);
	init_fds_count_redirs(&ms->struct_count, input);
	cmd = ft_calloc(ms->struct_count + 1, sizeof(t_command));
	if (!cmd)
		malloc_error();
	while (track < ms->struct_count + 1)
	{
		cmd[track].redir_fd_index_in = -2;
		cmd[track].redir_fd_index_out = -2;
		track++;
	}
	put_cmds_to_struct(cmd, input, ms);
	full_cmd(cmd, ms->struct_count, track);
	return (cmd);
}
