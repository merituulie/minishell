/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/26 07:48:29 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/// @brief Inner loop for parsing trough strings in array.
/// @param array
/// @param deli index where delimeter is found.
/// @param del_line_index index of the line in array, where delimeter is found.
char	**add_line(char **array, int deli, int del_line_index)
{
	char	**n_array;
	int		i;

	n_array = allocate_2d_array(array);
	i = -1;
	if (del_line_index == 0)
	{
		n_array[0] = ft_substr(array[0], 0, deli);
		n_array[1] = ft_substr(array[0], deli, (ft_strlen(array[0]) - deli));
	}
	else
	{
		while (++i < ft_arrlen(array))
		{
			if (i == del_line_index)
			{
				n_array[i] = ft_substr(array[i], 0, deli);
				n_array[i + 1] = ft_substr(array[i], deli, ft_strlen(array[i]));
			}
			else
				n_array[i] = ft_strdup(array[i]);
		}
	}
	ft_free_array(array);
	return (n_array);
}

/// @brief Inner loop for parsing trough strings in array.
/// @param array
/// @param del_i index where delimeter is found.
/// @param del_li index of the line in array, where delimeter is found.
/// @param dlen delimeter len (in case of redirectors and pipe)
char	**add_line_redir(char **array, t_lexer l)
{
	char	**n_array;
	int		i;

	printf("INSIDE add_line_redir:\nl.i = %i\nl.j = %i\n\n", l.i, l.j);
	n_array = allocate_2d_array(array);
	if (!n_array)
		return (NULL);
	i = -1;
	if (l.i == 0)
	{
		n_array[0] = ft_substr(array[0], l.j, l.del_len);
		n_array[1] = ft_substr(array[0], l.del_len, (ft_strlen(array[0]) - l.del_len));
	}
	else
	{
		while (++i < ft_arrlen(array))
		{
			if (i == l.i)
			{
				n_array[i] = ft_substr(array[i], l.j, l.del_len);
				n_array[i + 1] = ft_substr(array[i], l.del_len, ft_strlen(array[i]));
			}
			else
				n_array[i] = ft_strdup(array[i]);
		}
	}
	ft_free_array(array);
	return (n_array);
}

char	**parse_line_helper(char ***array, t_lexer l)
{
	char	**temp;

	temp = *array;
	while (++l.j < (int)ft_strlen(temp[l.i]))
	{
		if (is_operand(temp[l.i][0]) == true)
		{
			l.del_len = double_redir(temp[l.i], l.j);
			printf("BEFORE GOING IN TO add_line_redir:\nl.i = %i\nl.j = %i\n\n", l.i, l.j);
			temp = add_line_redir(temp, l);
			printf("ARRAY BACK IN parse_line_helper\n");
			ft_print_array(temp);
			if (!temp)
				return (NULL);
			trim_last_line(temp, l.i + 1); // PROTECT
			l.j = l.del_len;
		}
		else
		{
			if (temp[l.i][l.j] == 34 || temp[l.i][l.j] == 39)
				l.j = quote_index(temp[l.i], l.j);
			if (is_delim(temp[l.i][l.j]) == true || is_operand(temp[l.i][l.j]) == true)
			{
				temp = add_line(temp, l.j, l.i);
				trim_last_line(temp, l.i + 1); // PROTECT
			}
		}
	}
	return (temp);
}

/// @brief Outer loop for parsing trough strings in array.
/// @param array 2d array, holding whole input in array[0].
char	**parse_line(char **array, t_lexer l)
{
	// int	i;
	// int	j;
	// int	del_len;

	l.i = -1;
	l.del_len = 0;
	while (++l.i < ft_arrlen(array) && array[l.i])
	{
		l.j = -1;
		array = parse_line_helper(&array, l);
		if (array == NULL)
			return (NULL);
	}
	return (array);
}

void init_lexer(t_lexer *l)
{
	l->i = 0;
	l->j = 0;
	l->del_len = 0;
	l->arr = 0;
}

/// @param str user input from readline.
char	**ft_lexer(char *str)
{
	char	*trimmed_str;
	char	**new_str;
	// char	**parsed_line;
	int		len;
	t_lexer	l;

	init_lexer(&l);
	trimmed_str = ft_strtrim(str, " \t");
	len = ft_strlen(trimmed_str);
	if (syntax_error(trimmed_str) == -1)
		return (NULL);
	new_str = (char **)ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (NULL);
	new_str[0] = ft_strdup(trimmed_str);
	if (new_str == NULL)
		return (free(trimmed_str), NULL);
	l.arr = parse_line(new_str, l);
	if (!l.arr)
		return (NULL);
	ft_print_array(l.arr); //HOXHOXHOX
	return (l.arr);
}
