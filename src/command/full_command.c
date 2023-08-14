/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:02:40 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/10 14:01:56 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

void	put_fullcmd_input(t_command	*cmd, int i, int track, int index)
{
	int	j;

	j = 0;
	while (cmd[track].input[j])
	{
		cmd[i].full_cmd[j + index] = ft_strdup(cmd[track].input[j]);
		if (!cmd[i].full_cmd[j + index])
			ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
		j++;
	}
}

void	put_fullcmd(t_command *cmd, int i, int track)
{
	if (cmd[track].command == NULL)
		return ;
	cmd[i].full_cmd[0] = ft_strdup(cmd[track].command);
	if (!cmd[i].full_cmd[0])
		ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
	if (!cmd[track].flags && cmd[track].input)
		put_fullcmd_input(cmd, i, track, 1);
	else if (cmd[track].flags && !cmd[track].input)
	{
		cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
		if (!cmd[i].full_cmd[1])
			ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
	}
	else if (cmd[track].flags && cmd[track].input)
	{
		cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
		if (!cmd[i].full_cmd[1])
			ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
		put_fullcmd_input(cmd, i, track, 2);
	}
}

void	full_cmd(t_command *cmd, int struct_count, int track)
{
	int	i;

	if (struct_count == 1 && cmd->command == NULL)
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
			ft_putstr_fd("Memory allocation failure!\n", 2, 1);
		put_fullcmd(cmd, i, track);
		i++;
	}
}
