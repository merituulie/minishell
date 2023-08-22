/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:57:20 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:57:21 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	put_fullcmd_input(t_command	*cmd, int i, int track, int index)
{
	int	j;

	j = 0;
	while (cmd[track].input[j])
	{
		cmd[i].full_cmd[j + index] = ft_strdup(cmd[track].input[j]);
		if (!cmd[i].full_cmd[j + index])
			malloc_error();
		j++;
	}
}

void	put_fullcmd(t_command *cmd, int i, int track)
{
	if (!cmd[track].command)
		return ;
	cmd[i].full_cmd[0] = ft_strdup(cmd[track].command);
	if (!cmd[i].full_cmd[0])
		malloc_error();
	if (!cmd[track].flags && cmd[track].input)
		put_fullcmd_input(cmd, i, track, 1);
	else if (cmd[track].flags && !cmd[track].input)
	{
		cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
		if (!cmd[i].full_cmd[1])
			malloc_error();
	}
	else if (cmd[track].flags && cmd[track].input)
	{
		cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
		if (!cmd[i].full_cmd[1])
			malloc_error();
		put_fullcmd_input(cmd, i, track, 2);
	}
}

void	full_cmd(t_command *cmd, int struct_count, int track)
{
	int	i;

	if (struct_count == 1 && !cmd->command)
		return ;
	track = -1;
	i = 0;
	while (++track < struct_count)
	{
		if (track >= struct_count)
			break ;
		if (!cmd[track].flags && !cmd[track].input)
			cmd[i].full_cmd = ft_calloc(2, sizeof (char *));
		else if (cmd[track].flags && !cmd[track].input)
			cmd[i].full_cmd = ft_calloc(3, sizeof (char *));
		else if (!cmd[track].flags && cmd[track].input)
			cmd[i].full_cmd = ft_calloc(ft_arrlen(cmd[track].input) + 2, \
			sizeof (char *));
		else
			cmd[i].full_cmd = ft_calloc(ft_arrlen(cmd[track].input) + 3, \
			sizeof (char *));
		if (!cmd[i].full_cmd)
			malloc_error();
		put_fullcmd(cmd, i, track);
		i++;
	}
}
