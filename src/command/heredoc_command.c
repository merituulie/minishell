/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_Command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:11:37 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/02 18:14:03 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_for_cat_grep(char *str)
{
	if (!ft_strncmp_all("cat", str) || !ft_strncmp_all("grep", str))
		return (1);
	return (0);
}

int	handle_heredoc(t_command *cmd, int *index, int track, char **input)
{
	int	cmd_index;

	cmd_index = 0;
	if (!ft_strncmp_all("<<", input[(*index)]))
	{
		if ((*index) > 0 && input[(*index) - 1] \
		&& input[(*index) - 1][0] != '|')
			cmd_index = (*index) - 1;
		else if (input[(*index) + 1] && input[(*index) + 2] \
		&& input[(*index) + 2][0] != '|')
			cmd_index = (*index) + 2;
		if (check_for_cat_grep(input[cmd_index]))
			cmd[track].infile_name = ft_strdup(HEREDOC);
		(*index) += 2;
		return (1);
	}
	return (0);
}
