/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lines_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:17:58 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/26 14:33:53 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

char	**not_first_line(char **n_array, t_lexer *l)
{
	int	i;

	i = -1;
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

	n_array = allocate_2d_array(l->new_arr);
	if (!n_array)
		return (NULL);
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

	// printf("INSIDE add_line_redir:\nl.i = %i\nl.j = %i\n\n", l.i, l.j);
	n_array = allocate_2d_array(l->new_arr);
	if (!n_array)
		return (NULL);
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
