/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/07 07:10:04 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

char	**add_line(char **old_array, size_t del_index, int del_line_index)
{
	char	**new_array;
	int		i;

	new_array = allocate_2d_array(old_array);
	i = -1;
	if (del_line_index == 0)
	{
		new_array[0] = ft_substr(old_array[0], 0, del_index);
		new_array[1] = ft_substr(old_array[0], del_index, (ft_strlen(old_array[0]) - del_index));
	}
	else
	{
		while (++i < ft_arrlen(old_array))
		{
			if (i == del_line_index)
			{
				new_array[i] = ft_substr(old_array[i], 0, del_index);
				new_array[i + 1] = ft_substr(old_array[i], del_index, ft_strlen(old_array[i]));
			}
			else
				new_array[i] = ft_strdup(old_array[i]);
		}
	}
	ft_free_array(old_array);
	return (new_array);
}

char	**add_line_redir(char **old_array, size_t del_index, int del_line_index, size_t del_len)
{
	char	**new_array;
	int		i;

	new_array = allocate_2d_array(old_array);
	i = -1;
	if (del_line_index == 0)
	{
		new_array[0] = ft_substr(old_array[0], del_index, del_len);
		new_array[1] = ft_substr(old_array[0], del_len, (ft_strlen(old_array[0]) - del_len));
	}
	else
	{
		while (++i < ft_arrlen(old_array))
		{
			if (i == del_line_index)
			{
				new_array[i] = ft_substr(old_array[i], del_index, del_len);
				new_array[i + 1] = ft_substr(old_array[i], del_len, ft_strlen(old_array[i]));
			}
			else
				new_array[i] = ft_strdup(old_array[i]);
		}
	}
	ft_free_array(old_array);
	return (new_array);
}

char	**parse_line(char **array) // NEEDS TO BE SHORTENED
{
	size_t		i;
	size_t		j;
	// size_t		arrlen;
	size_t		del_len;

	i = -1;
	while (++i < ft_arrlen(array) && array[i])
	{
		j = -1;
		while (++j < ft_strlen(array[i]))
		{
			if (is_operand(array[i][0]) == true)
			{
				del_len = double_redir(array[i], j);
				array = add_line_redir(array, j, i, del_len);
				trim_last_line(array, i + 1);
				j = del_len;
			}
			else
			{
				if (array[i][j] == 34 || array[i][j] == 39)
					j = quote_index(array[i], j);
				if (is_delim(array[i][j]) == true || is_operand(array[i][j]) == true)
				{
					array = add_line(array, j, i);
					trim_last_line(array, i + 1);
				}
			}
		}
	}
	return (array);
}

char	**ft_lexer(char *str)
{
	char	*trimmed_str;
	char	**new_str;
	char	**parsed_line;
	int		len;

	trimmed_str = ft_strtrim(str, " \t");
	len = ft_strlen(trimmed_str);
	syntax_error(trimmed_str);
	new_str = (char **)ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (0);
	new_str[0] = ft_strdup(trimmed_str);
	free(trimmed_str);
	parsed_line = parse_line(new_str);
	return (parsed_line);
}
