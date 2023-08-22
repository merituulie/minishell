/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:55:04 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:56:01 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

// 1 -> |
// 2 -> <, or >, or <<, or >>
int	syntax_error_msg(int i, char *str)
{
	if (i == 1)
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2, 1);
	if (i == 2)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2, 1);
	if (i == 3)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2, 1);
	if (i == 4)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2, 1);
	if (i == 5)
		ft_putstr_fd("syntax error: quotes not ended\n", 2, 1);
	free(str);
	set_exit_code(258);
	return (-1);
}

char	**allocate_2d_array(char **old_array)
{
	char	**new_array;
	size_t	arr_len;

	if (!old_array)
		return (NULL);
	arr_len = ft_arrlen(old_array);
	new_array = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!new_array)
		malloc_error();
	return (new_array);
}

int	trim_last_line(char **array, int line_index)
{
	char	*new_last_line;

	if (array[line_index][0] == 32)
	{
		new_last_line = ft_strtrim(array[line_index], " \t\n");
		if (!new_last_line)
		{
			free(array[line_index]);
			return (0);
		}
		free(array[line_index]);
		array[line_index] = new_last_line;
	}
	return (1);
}

int	check_if_nothing(char *str, int i)
{
	while (str[i] && is_delim(str[i]) == true)
	{
		i++;
	}
	if (!str[i])
		return (1);
	return (0);
}

int	quote_check(char *str, int i, char quote)
{
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (syntax_error_msg(5, str));
}
