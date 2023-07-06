/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:19:51 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/06 11:00:07 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

char	**allocate_2d_array(char **old_array)
{
	char	**new_array;
	size_t	arr_len;

	arr_len = ft_arrlen(old_array);
	new_array = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	return (new_array);
}

void	**trim_last_line(char **array, int line_index)
{
	size_t	arr_len;
	char	*new_last_line;

	if (array[line_index][0] == 32)
	{
		new_last_line = ft_strtrim(array[line_index], " \t\n");
		free(array[line_index]);
		array[line_index] = new_last_line;
	}
}
