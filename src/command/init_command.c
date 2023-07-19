/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/19 11:12:11 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

static char	*put_to_input(char **input, int *index)
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
	str = malloc(sizeof(char) * (str_len + space_count + 1));
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	while (++cur_index < *index)
	{
		ft_strlcat(str, " ", str_len + space_count + 1);
		ft_strlcat(str, input[cur_index], str_len + space_count + 1);
	}
	return (str);
}

static char	*put_to_flags(char **input, int	*index)
{
	int	cur_index;

	cur_index = *index;
	if (input[*index][0] == '-')
	{
		(*index)++;
		return (input[cur_index]);
	}
	else
		return (NULL);
}

void	put_full_cmd(t_command *cmd, int struct_count, int track)
{
	track = -1;
	while (++track < struct_count)
	{
		if (ft_strchr("<>", cmd[track].command[0]))
			return ;
		else
			cmd[track].full_cmd = ft_calloc(4, sizeof (char *));
		cmd[track].full_cmd[0] = ft_strdup(cmd[track].command);
		if (!cmd[track].flags && cmd[track].input)
			cmd[track].full_cmd[1] = ft_strdup(cmd[track].input);
		else if (cmd[track].flags && !cmd[track].input)
			cmd[track].full_cmd[1] = ft_strdup(cmd[track].flags);
		else if (cmd[track].flags && cmd[track].input)
		{
			cmd[track].full_cmd[1] = ft_strdup(cmd[track].flags);
			cmd[track].full_cmd[2] = ft_strdup(cmd[track].input);
		}
	}
}

void	put_cmd_to_struct(t_command *cmd, int index, \
		int struct_count, char **input)
{
	int		track;
	char	*str;

	track = -1;
	while (++track < struct_count)
	{
		if (ft_strchr("|", input[index][0]))
			index++;
		cmd[track].command = ft_strdup(input[index++]);
		if (!cmd[track].command)
			printf("strdup allocation fail!");
		if (input[index] == NULL)
			return ;
		str = put_to_flags(input, &index);
		strdup_if_not_null(cmd, track, "flags", str);
		str = NULL;
		if (input[index] == NULL)
			return ;
		str = put_to_input(input, &index);
		strdup_if_not_null(cmd, track, "input", str);
		str = NULL;
	}
}

/*only handles pipe now. <, >, >>. < cases are not handled*/
t_command	*init_cmds(t_data *ms, char **input)
{
	t_command	*cmd;
	int			index;
	int			track;

	index = 0;
	ms->struct_count = 0;
	track = 0;
	ms->struct_count = count_struct(input, ms->struct_count);
	printf("struct count is %d\n", ms->struct_count);
	cmd = ft_calloc(ms->struct_count + 1, sizeof(t_command));
	put_cmd_to_struct(cmd, index, ms->struct_count, input);
	put_full_cmd(cmd, ms->struct_count, track);
	return (cmd);
}
