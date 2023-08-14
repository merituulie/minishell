/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:08:21 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/14 18:53:43 by meskelin         ###   ########.fr       */
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
		if (ft_strchr("|", input[index][0]))
		{
			index++;
			track++;
			continue ;
		}
		parse_command(cmd, track, &index, input);
	}
}
