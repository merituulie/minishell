/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:42 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/20 11:08:49 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

char	*put_to_input(char **input, int *index)
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

char	*put_to_flags(char **input, int	*index)
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

char	*put_to_file(char **input, int **index)
{
	int		str_len;
	int		cur_index;
	char	*str;

	str_len = 0;
	cur_index = **index;
	if (ft_strchr_null("<|>", input[**index][0]))
		return (NULL);
	str_len += ft_strlen(input[**index]);
	(**index)++;
	str = malloc(sizeof(char) * (str_len + 1));
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	printf("str is %s\n", str);
	return (str);
}

void	put_redirection(t_command *cmd, int *index, int track, char **input)
{
	char	*str;

	if (!ft_strncmp_all("<<", cmd[track].command))
	{
		str = put_to_file(input, &index);
		strdup_if_not_null(cmd, track, "input", str);
	}
	else
	{
		str = put_to_file(input, &index);
		strdup_filename(cmd, track, str);
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
		if (ft_strchr("<>", cmd[track].command[0]))
			put_redirection(cmd, &index, track, input);
		else
		{
			if (input[index] == NULL)
				return ;
			str = put_to_flags(input, &index);
			strdup_if_not_null(cmd, track, "flags", str);
			if (input[index] == NULL)
				return ;
			str = put_to_input(input, &index);
			strdup_if_not_null(cmd, track, "input", str);
		}
	}
}
