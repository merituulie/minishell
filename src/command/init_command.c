/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/20 11:25:00 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

int	count_struct(char **input, int struct_count)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if ((ft_strchr_null("<|>", input[index][0])) || index == 0)
		{
			if (ft_strchr_null("<", input[index][0]) && \
								(index + 2) < ft_arrlen(input))
			{
				if (input[index + 2][0] && !ft_strchr_null("<|>", \
									input[index + 2][0]))
					struct_count++;
			}
			struct_count++;
			index++;
		}
		else
			index++;
	}
	return (struct_count);
}

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
	full_cmd(cmd, ms->struct_count, track);
	free_str_array(input);
	return (cmd);
}
