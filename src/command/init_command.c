/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/17 11:35:13 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"

//here it <<, >> case should be added.
static int	count_struct(char **input, int struct_count)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if ((ft_strchr("<|>", input[index][0])) || index == 0)
		{
			struct_count++;
			index++;
		}
		else
			index++;
	}
	return (struct_count);
}

static char	*put_to_input(char **input, int *index)
{
	int		str_len;
	int		cur_index;
	char	*str;
	int		space_count;

	space_count = -1;
	str_len = 0;
	cur_index = *index;
	while (input[*index] != NULL && !ft_strchr("<|>", input[*index][0]))
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

void	put_cmd_to_struct(t_command *cmd, int index, \
		int struct_count, char **input)
{
	int		track;
	char	*str;

	track = -1;
	while (++track < struct_count)
	{
		printf("index is %d\n", index);
		if (ft_strchr("|", input[index][0]))
			index++;
		cmd[track].command = ft_strdup(input[index++]);
		printf("cmd[%d].command is %s\n", track, cmd[track].command);
		cmd[track].flags = put_to_flags(input, &index);
		printf("cmd[%d].flags is %s\n", track, cmd[track].flags);
		str = put_to_input(input, &index);
		cmd[track].input = ft_strdup(str);
		printf("cmd[%d].input is %s\n", track, cmd[track].input);
		free(str);
	}
}

/*only handles pipe now. <, >, >>. < cases are not handled*/
t_command	*init_cmds(char **input)
{
	t_command	*cmd;
	int			index;
	int			struct_count;

	index = 0;
	struct_count = 0;
	struct_count = count_struct(input, struct_count);
	printf("struct count is %d\n", struct_count);
	cmd = ft_calloc(struct_count + 1, sizeof(t_command));
	put_cmd_to_struct(cmd, index, struct_count, input);
	printf("---before returning to main\n");
	return (cmd);
}
