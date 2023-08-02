/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:07:50 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/02 15:20:34 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

char	**copy_input(char **input, int *index)
{
	int		cur_index;
	char	**out;
	int		i;

	i = 0;
	cur_index = *index;
	if (ft_strchr_null("<|>", input[*index][0]))
		return (NULL);
	while ((*index) < ft_arrlen(input) && \
			!ft_strchr_null("<|>", input[*index][0]))
		(*index)++;
	out = ft_calloc(((*index) - cur_index + 1), sizeof(char *));
	if (!out)
		printf("memory allocation error\n");
	while (cur_index < (*index))
	{
		out[i] = ft_strdup(input[cur_index]);
		i++;
		cur_index++;
	}
	out[i] = NULL;
	i = -1;
	return (out);
}

static void	put_to_input2(t_command *cmd, int track, char **not_echo)
{
	int	i;
	int	len;

	i = 0;
	if (not_echo == NULL)
		cmd[track].input = NULL;
	len = ft_arrlen(not_echo);
	cmd[track].input = ft_calloc(len + 1, sizeof (char *));
	if (!cmd[track].input)
		printf("calloc fail!\n");
	while (not_echo[i])
	{
		cmd[track].input[i] = ft_strdup(not_echo[i]);
		if (!cmd[track].input[i])
			printf("strdup allocation fail!\n");
		i++;
	}
	cmd[track].input[i] = NULL;
}

void	put_to_input(t_command *cmd, int track, char *str, char **not_echo)
{
	if (!ft_strncmp_all(cmd[track].command, "echo"))
	{
		if (str == NULL)
			cmd[track].input = NULL;
		else
		{
			cmd[track].input = ft_calloc(2, sizeof (char *));
			if (!cmd[track].input)
				printf("calloc fail!\n");
			cmd[track].input[0] = ft_strdup(str);
			if (!cmd[track].input[0])
				printf("strdup allocation fail!\n");
			cmd[track].input[1] = NULL;
		}
	}
	else
		put_to_input2(cmd, track, not_echo);
}

void	put_fullcmd_input(t_command	*cmd, int i, int track, int index)
{
	int	j;

	j = 0;
	while (cmd[track].input[j])
	{
		cmd[i].full_cmd[j + index] = ft_strdup(cmd[track].input[j]);
		if (!cmd[i].full_cmd[j + index])
			printf("strdup fail!\n");
		j++;
	}
}
