/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/26 10:52:09 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

char	**not_first_line(char **n_array, t_lexer *l)
{
	int	i;

	i = 1;
	while (++i < ft_arrlen(l->new_arr))
	{
		if (i == l->i)
		{
			n_array[i] = ft_substr(l->new_arr[i], 0, l->j);
			if (!n_array[i])
				return (NULL);
			n_array[i + 1] = ft_substr(l->new_arr[i], l->j, \
				ft_strlen(l->new_arr[i]));
			if (!n_array[i + 1])
				return (NULL);
		}
		else
			n_array[i] = ft_strdup(l->new_arr[i]);
			if (!n_array[i])
				return (NULL);
	}
	return (n_array);
}

/// @brief Inner loop for parsing trough strings in array.
/// @param array
/// @param deli index where delimeter is found.
/// @param del_line_index index of the line in array, where delimeter is found.
char	**add_line(t_lexer *l)
{
	char	**n_array;
	// int		i;

	n_array = allocate_2d_array(l->new_arr);
	if (!n_array)
		return (NULL);
	// i = -1;
	if (l->i == 0)
	{
		n_array[0] = ft_substr(l->new_arr[0], 0, l->j);
		n_array[1] = ft_substr(l->new_arr[0], l->j, (ft_strlen(l->new_arr[0]) - l->j));
	}
	else
	{
		n_array = not_first_line(n_array, l);
		if (!n_array)
			return (NULL);
	}
	return (n_array);
}

char	**not_first_line_redir(char **n_array, t_lexer *l)
{
	int	i;

	i = -1;
	while (++i < ft_arrlen(l->new_arr))
	{
		if (i == l->i)
		{
			n_array[i] = ft_substr(l->new_arr[i], l->j, l->del_len);
			if (!n_array[i])
				return (NULL);
			n_array[i + 1] = ft_substr(l->new_arr[i], l->del_len, \
				ft_strlen(l->new_arr[i]));
			if (!n_array[i + 1])
				return (NULL);
		}
		else
		{
			n_array[i] = ft_strdup(l->new_arr[i]);
			if (!n_array[i])
				return (NULL);
		}
	}
	return (n_array);
}

/// @brief Inner loop for parsing trough strings in array.
/// @param array
/// @param del_i index where delimeter is found.
/// @param del_li index of the line in array, where delimeter is found.
/// @param dlen delimeter len (in case of redirectors and pipe)
char	**add_line_redir(t_lexer *l)
{
	char	**n_array;
	// int		i;

	// printf("INSIDE add_line_redir:\nl.i = %i\nl.j = %i\n\n", l.i, l.j);
	n_array = allocate_2d_array(l->new_arr);
	if (!n_array)
		return (NULL);
	// i = -1;
	if (l->i == 0)
	{
		n_array[0] = ft_substr(l->new_arr[0], l->j, l->del_len);
		n_array[1] = ft_substr(l->new_arr[0], l->del_len, \
			(ft_strlen(l->new_arr[0]) - l->del_len));
	}
	else
	{
		n_array = not_first_line_redir(n_array, l);
		if (!n_array)
			return (NULL);
	}
	return (n_array);
}

/// @brief if lines first index is <, | or >
/// @param l structure from lexer.h
/// @return if failed returns 0, if success returns 1
int	case_operand(t_lexer *l)
{
		printf("ARRAY WHEN ARRIVING IN check_operand\n");
		ft_print_array(l->new_arr);
		l->del_len = double_redir(l->new_arr[l->i], l->j);
		l->new_arr = add_line_redir(l);
		if (!l->new_arr)
			return (0);
		if (trim_last_line(l->new_arr, l->i + 1) == 0)
			return (0);
		l->j = l->del_len;
		printf("ARRAY WHEN LEAVING check_operand\n");
		ft_print_array(l->new_arr);
		return (1);
}

char	**parse_line_helper(t_lexer *l)
{
	while (++l->j < (int)ft_strlen(l->new_arr[l->i]))
	{

		if (is_operand(l->new_arr[l->i][0]) == true)
		{
			if (case_operand(l) == 0)
				return (NULL);
			// printf("ARRAY BACK IN parse_line_helper\n");
			// ft_print_array(l->new_arr);
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

/// @brief Outer loop for parsing trough strings in array.
/// @param array 2d array, holding whole input in array[0].
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

void	init_lexer(t_lexer *l)
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
	int		len;
	t_lexer	l;

	init_lexer(&l);
	trimmed_str = ft_strtrim(str, " \t");
	len = ft_strlen(trimmed_str);
	if (syntax_error(trimmed_str) == -1)
		return (NULL);
	l.new_arr = (char **)ft_calloc(2, sizeof(char *));
	if (!l.new_arr)
		return (NULL);
	l.new_arr[0] = ft_strdup(trimmed_str);
	if (l.new_arr == NULL)
		return (free(trimmed_str), NULL);
	l.arr = parse_line(l);
	if (!l.arr)
		return (NULL);
	 //HOXHOXHOX
	printf("ARRAY BACK IN ft_lexer\n");
	ft_print_array(l.arr);
	printf("**********************\n");
	return (l.arr);
}
