/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:19:51 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/06 10:27:36 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

bool	is_delim(char c)
{
	char	*delims;

	delims = " \t\n";
	while (*delims)
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}

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

int	quote_index(char *str, int j)
{
	int	temp;

	temp = j;
	while (str[temp++])
	{
		if (str[temp] == str[j])
			return (temp);
	}
	return (j);
}

int	double_redir(char *str, int j)
{
	if (str[j] != '<' && str[j] != '>' && str[j] != '|')
		return (0);
	if (str[j] == '<' || str[j] == '>' || str[j] == '|')
	{
		if (str[j] == str[j + 1])
			return (2);
		else
			return (1);
	}
}
