/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:42 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/01 13:18:38 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

char	*parse_input(char **input, int *index)
{
	int		str_len;
	int		cur_index;
	char	*str;
	int		space_count;

	space_count = -1;
	str_len = 0;
	cur_index = *index;
	if (ft_strchr_null("<|>", input[*index][0]))
		return (NULL);
	while ((*index) < ft_arrlen(input) && \
	!ft_strchr_null("<|>", input[*index][0]))
	{
		str_len += ft_strlen(input[*index]);
		(*index)++;
		space_count++;
	}
	str = ft_calloc((str_len + space_count + 1), sizeof(char));
	if (!str)
		printf("memory allocation error\n");
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	while (++cur_index < *index)
	{
		ft_strlcat(str, " ", str_len + space_count + 1);
		ft_strlcat(str, input[cur_index], str_len + space_count + 1);
	}
	return (str);
}

char	*parse_flags(char **input, int	*index)
{
	int	cur_index;

	cur_index = *index;
	if (input[*index][0] == '-')
	{
		(*index)++;
		return (ft_strdup(input[cur_index]));
	}
	else
		return (NULL);
}

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
		printf("memory allocation fail\n");
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	return (str);
}

void	handle_redirection(t_command *cmd, int *index, int track, char **input)
{
	char		*str;

	str = NULL;
	cmd[track].token = NONE;
	while (ft_strchr_null("<>", input[(*index)][0]) \
	&& !ft_strchr_null("<", input[(*index)][1]))
	{
		if (ft_strncmp(input[(*index)], "<", 1) && cmd[track].infile_name)
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		if (ft_strncmp(input[(*index)], ">", 1) && cmd[track].outfile_name)
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		str = parse_redirection_filename(input, (*index + 1));
		parse_redirection(cmd, track, str, input[(*index)]);
		open_redirection_file(&cmd[track]);
		if (!input[(*index + 2)])
		{
			(*index) += 2;
			break ;
		}
		else
			(*index) += 2;
	}
	free(str);
}

static void	parse_command(t_command *cmd, int track, int *index, char **input)
{
	char	*str;

	cmd[track].command = ft_strdup(input[(*index)++]);
	if (!cmd[track].command)
		printf("strdup allocation fail!");
	if (!input[(*index)])
		return ;
	str = parse_flags(input, &(*index));
	put_to_flags(cmd, track, str);
	if (str)
		free(str);	
	if (!input[(*index)])
		return ;
	str = parse_input(input, index);
	put_to_input(cmd, track, str);
	if (str)
		free(str);	
}

static int	handle_heredoc(t_command *cmd, int *index, int *track, char **input)
{
	int	org_index;

	org_index = 0;
	if (!ft_strncmp_all("<<", input[(*index)]))
	{
		org_index = (*index);
		if ((*index) > 0 && input[(*index) - 1][0] \
		&& input[(*index) - 1][0] != '|')
		{
			parse_command(cmd, (*track), index, input);
			while ((*index) >= 0 && ft_strchr("<|>", input[(*index)][0]))
				(*index)--;
			(*track)++;
			return (org_index);
		}
		if (input[(*index) + 1][0] && input[(*index) + 2] \
		&& input[(*index) + 2][0] != '|')
		{
			cmd[(*track)].command = ft_strdup(input[(*index++)]);
			cmd[(*track)].input = ft_strdup(input[(*index++)]);
			track++;
		}
	}
	return (0);
}

void	put_cmds_to_struct(t_command *cmd, char **input)
{
	int		index;
	int		org_index;
	int		track;

	index = 0;
	track = 0;
	while (input[index])
	{
		org_index = handle_heredoc(cmd, &index, &track, input);
		if (org_index)
			index = org_index;
		handle_redirection(cmd, &index, track, input);
		if (!input[index])
			break ;
		if (ft_strchr("|", input[index][0]))
		{
			index++;
			track++;
		}
		parse_command(cmd, track, &index, input);
	}
}
