/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:15:27 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/20 13:01:07 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"
#include "../../headers/parsing.h"

static char	*delete_quotes_str(char *input, t_data *ms)
{
	int	i;

	i = -1;
	if (!input)
		return (NULL);
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			delete_quotes(input, i, ft_strlen(input), ms);
			free(input);
			input = ft_strdup(ms->out);
			if (!input)
				ft_putstr_fd("Memory allocation failure!\n", 2, 1);
			free(ms->out);
			ms->out = NULL;
			i = ms->end - 2;
		}
	}
	return (input);
}



void	delete_quotes_struct(t_command *cmd, t_data *ms)
{
	int		i;
	int		track;

	track = 0;
	while (track < ms->struct_count)
	{
		cmd[track].command = delete_quotes_str(cmd[track].command, ms);
		cmd[track].flags = delete_quotes_str(cmd[track].flags, ms);
		i = -1;
		while (cmd[track].input[++i])
		{
			cmd[track].input[i] = delete_quotes_str(cmd[track].input[i], ms);
		}
		track ++;
	}
}
