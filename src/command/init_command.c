/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/29 18:29:50 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

// static int	is_heredoc_has_command(char **input, int index)
// {
// 	if (input[index][1] == '<')
// 	{
// 		if ((index > 0 && input[index - 1][0] && input[index - 1][0] != '|') \
// 		|| (input[index + 2][0] && input[index + 2][0] != '|'))
// 			return (1);
// 	}
// 	return (0);
// }

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

static void	init_fds(int fd_count, char **input)
{
	int	index;

	fd_count = fd_count * 2 - 2;
	g_info.pipe_count = fd_count;
	g_info.pipe_fds = ft_calloc(g_info.pipe_count, sizeof(* g_info.pipe_fds));
	if (!g_info.pipe_fds)
		printf("memory allocation failed\n");
	index = 0;
	fd_count = 0;
	while (input[index])
	{
		if (ft_strchr_null("<>", input[index][0]))
			fd_count++;
		index++;
	}
	g_info.redir_count = fd_count;
	g_info.redir_fds = ft_calloc(g_info.redir_count, sizeof(* g_info.redir_fds));
	if (!g_info.redir_fds)
		printf("memory allocation failed\n");
}

t_command	*init_cmds(t_data *ms, char **input)
{
	t_command	*cmd;
	int			track;

	ms->struct_count = 0;
	track = 0;
	ms->struct_count = count_struct(input);
	init_fds(ms->struct_count, input);
	printf("struct count is: %i\n", ms->struct_count);
	cmd = ft_calloc(ms->struct_count + 1, sizeof(t_command));
	if (!cmd)
		printf("memory allocation error\n");
	put_cmds_to_struct(cmd, input);
	full_cmd(cmd, ms->struct_count, track);
	free_str_array(input);
	return (cmd);
}
