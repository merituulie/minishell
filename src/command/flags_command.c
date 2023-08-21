/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:06:48 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/21 16:09:53 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

void	put_to_flags(t_command **cmd, int track, char *str)
{
	if (str == NULL)
		(*cmd)[track].flags = NULL;
	else
	{
		(*cmd)[track].flags = ft_strdup(str);
		if (!(*cmd)[track].flags)
			malloc_error();
	}
}
