/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/28 11:41:37 by rmakinen         ###   ########.fr       */
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

// int	count_struct(char **input, int struct_count)
// {
// 	int	index;

// 	index = 0;
// 	while (input[index])
// 	{
// 		if ((ft_strchr_null("<|>", input[index][0])) || index == 0)
// 		{
// 			if (ft_strchr_null("<", input[index][0]) && \
// 								(index + 2) < ft_arrlen(input))
// 			{
// 				if (input[index + 2][0] && !ft_strchr_null("<|>", \
// 									input[index + 2][0]))
// 					struct_count++;
// 			}
// 			struct_count++;
// 			index++;
// 		}
// 		else
// 			index++;
// 	}
// 	return (struct_count);
// }

t_command	*init_cmds(t_data *ms, char **input)
{
	t_command	*cmd;
	int			track;

	ms->struct_count = 0;
	track = 0;
	ms->struct_count = count_struct(input);
	printf("struct count is: %i\n", ms->struct_count);
	cmd = ft_calloc(ms->struct_count + 1, sizeof(t_command));
	if (!cmd)
		printf("memory allocation error\n");
	put_cmds_to_struct(cmd, input);
	full_cmd(cmd, ms->struct_count, track);
	free_str_array(input);
	return (cmd);
}
