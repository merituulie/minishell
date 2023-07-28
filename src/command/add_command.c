/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:42 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/28 13:52:23 by rmakinen         ###   ########.fr       */
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
		return (input[cur_index]);
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
	printf("parse_redirection_input cur_index %d\n", cur_index);
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
	char	*str;
	int 	temp;

	temp = *index;
	temp++;
	cmd[track].token = NONE;
	if (ft_strchr("<>", input[(*index)][0]))
	{
		str = parse_redirection_filename(input, temp);
		parse_redirection(cmd, track, str, input[(*index)]);
		(*index) += 2;
	}
}

void	put_cmds_to_struct(t_command *cmd, char **input)
{
	int		index;
	int		track;
	char	*str;

	index = 0;
	track = 0;
	while (input[index])
	{
		handle_redirection(cmd, &index, track, input);
		if (!input[index])
			break ;
		if (ft_strchr("|", input[index][0]))
		{
			index++;
			track++;
		}
		cmd[track].command = ft_strdup(input[index++]);
		if (!cmd[track].command)
			printf("strdup allocation fail!");
		if (!input[index])
			break ;
		str = parse_flags(input, &index);
		put_to_flags(cmd, track, str);
		if (!input[index])
			break ;
		str = parse_input(input, &index);
		put_to_input(cmd, track, str);
	}
}
