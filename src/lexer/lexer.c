/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/25 15:57:27 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/// @brief Inner loop for parsing trough strings in array.
/// @param array
/// @param deli index where delimeter is found.
/// @param del_line_index index of the line in array, where delimeter is found.
char	**add_line(char **array, size_t deli, int del_line_index)
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
/// @param delli index of the line in array, where delimeter is found.
/// @param dlen delimeter len (in case of redirectors and pipe)
char	**add_line_redir(char **array, size_t del_i, int del_li, size_t dlen)
{
	char	**n_array;
	int		i;

	n_array = allocate_2d_array(array);
	if (!n_array)
		return (NULL);
	i = -1;
	if (del_li == 0)
	{
		n_array[0] = ft_substr(array[0], del_i, dlen);
		n_array[1] = ft_substr(array[0], dlen, (ft_strlen(array[0]) - dlen));
	}
	else
	{
		while (++i < ft_arrlen(array))
		{
			if (i == del_li)
			{
				n_array[i] = ft_substr(array[i], del_i, dlen);
				n_array[i + 1] = ft_substr(array[i], dlen, ft_strlen(array[i]));
			}
			else
				n_array[i] = ft_strdup(array[i]);
		}
	}
	ft_free_array(array);
	return (n_array);
}

char	**parse_line_helper(char ***array, size_t i, size_t j, size_t del_len)
{
	char	**temp;

	temp = *array;
	while (++j < ft_strlen(temp[i]))
	{
		if (is_operand(temp[i][0]) == true)
		{
			del_len = double_redir(temp[i], j);
			temp = add_line_redir(temp, j, i, del_len);
			if (!temp)
				return (NULL);
			if (trim_last_line(temp, i + 1) == NULL)
				return (NULL);
			j = del_len;
		}
		else
		{
			if (temp[i][j] == 34 || temp[i][j] == 39)
				j = quote_index(temp[i], j);
			if (is_delim(temp[i][j]) == true || is_operand(temp[i][j]) == true)
			{
				temp = add_line(temp, j, i);
				trim_last_line(temp, i + 1);
			}
		}
	}
	return (temp);
}

/// @brief Outer loop for parsing trough strings in array.
/// @param array 2d array, holding whole input in array[0].
char	**parse_line(char **array)
{
	int		i;
	size_t	j;
	size_t	del_len;

	i = -1;
	del_len = 0;
	while (++i < ft_arrlen(array) && array[i])
	{
		j = -1;
		array = parse_line_helper(&array, i, j, del_len);
		if (array == NULL)
			return (NULL);
	}
	return (array);
}

/// @param str user input from readline.
char	**ft_lexer(char *str)
{
	char	*trimmed_str;
	char	**new_str;
	char	**parsed_line;
	int		len;

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
	// free(trimmed_str);
	parsed_line = parse_line(new_str);
	if (!parsed_line)
		return (NULL);
	ft_print_array(parsed_line); //HOXHOXHOX
	return (parsed_line);
}
