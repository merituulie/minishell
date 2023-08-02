/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:28:08 by jhusso            #+#    #+#             */
/*   Updated: 2023/08/02 10:25:42 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

char	**parse_line_helper(t_lexer *l)
{
	while (++l->j < (int)ft_strlen(l->new_arr[l->i]))
	{
		if (is_operand(l->new_arr[l->i][0]) == true)
		{
			if (case_operand(l) == 0)
				return (NULL);
		}
		else
		{
			if (l->new_arr[l->i][l->j] == 34 || l->new_arr[l->i][l->j] == 39)
				l->j = quote_index(l->new_arr[l->i], l->j);
			if (is_delim(l->new_arr[l->i][l->j]) == true \
				|| is_operand(l->new_arr[l->i][l->j]) == true)
			{
				l->new_arr = add_line(l);
				if (!l->new_arr)
					return (NULL);
				if (trim_last_line(l->new_arr, l->i + 1) == 0)
					return (NULL);
			}
		}
	}
	return (l->new_arr);
}

char	**parse_line(t_lexer l)
{
	l.i = -1;
	l.del_len = 0;
	while (++l.i < ft_arrlen(l.new_arr) && l.new_arr[l.i])
	{
		l.j = -1;
		l.new_arr = parse_line_helper(&l);
		if (l.new_arr == NULL)
			return (NULL);
	}
	return (l.new_arr);
}

static void	init_lexer(t_lexer *l)
{
	l->i = 0;
	l->j = 0;
	l->del_len = 0;
	l->arr = 0;
	l->new_arr = 0;
}

/// @param str user input from readline.
char	**ft_lexer(char *str)
{
	char	*trimmed_str;
	t_lexer	l;

	init_lexer(&l);
	trimmed_str = ft_strtrim(str, " \t");
	if (syntax_error(trimmed_str) == -1)
		return (NULL);
	l.new_arr = (char **)ft_calloc(2, sizeof(char *));
	if (!l.new_arr)
		return (NULL);
	l.new_arr[0] = ft_strdup(trimmed_str);
	free(trimmed_str);
	if (l.new_arr == NULL)
		return (NULL);
	l.arr = parse_line(l);
	if (!l.arr)
		return (NULL);
	return (l.arr);
}
