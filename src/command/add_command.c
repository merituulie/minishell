/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:15:26 by jhusso            #+#    #+#             */
/*   Updated: 2023/08/20 11:43:34 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

static void	parse_command(t_command *cmd, int track, int *index, char **input)
{
	char	*str;
	char	**not_echo;

	not_echo = NULL;
	str = NULL;
	if (!cmd[track].command)
		cmd[track].command = ft_strdup(input[(*index)++]);
	if (!cmd[track].command)
		ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
	if (!input[(*index)] || ft_strchr_null("<|>", input[*index][0]))
		return ;
	str = ft_strdup(parse_flags(input, &(*index)));
	put_to_flags(&cmd, track, str);
	if (str)
		free(str);
	if (!input[(*index)] || ft_strchr_null("<|>", input[*index][0]))
		return ;
	if (!ft_strncmp_all(cmd[track].command, "echo"))
		str = parse_input(input, index);
	else
		not_echo = copy_input(input, index, not_echo);
	put_to_input(cmd, track, str, not_echo);
}

void	put_cmds_to_struct(t_command *cmd, char **input, t_data *ms)
{
	int		index;
	int		track;

	index = 0;
	track = 0;
	while (input[index])
	{
		if (handle_heredoc(cmd, &index, track, input))
		{
			ft_heredoc(&cmd[track], &ms->env, input[index - 1]);
			continue ;
		}
		if (check_null_index_handle_redirs(cmd, track, input, &index) == -1)
			break ;
		if (ft_strchr_null("<>", input[(index)][0]))
			continue ;
		if (ft_strchr("|", input[index][0]))
		{
			index++;
			track++;
			continue ;
		}
		parse_command(cmd, track, &index, input);
	}
	delete_quotes_struct(cmd, ms);
}
