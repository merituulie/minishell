/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/03 07:57:10 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

size_t	ft_arrlen(const char **array)
{
	size_t	counter;

	counter = 0;
	while (*array != '\0')
	{
		counter++;
		array++;
	}
	// printf("arrlen in function= %i\n", counter);
	return (counter);
}

bool	is_delim(char c)
{
	char *delims;

	delims = " \t\n";
	while (*delims)
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}
char **allocate_2d_array(char **old_array)
{
	char	**new_array;
	size_t	arr_len;

	arr_len = ft_arrlen(old_array);
	new_array = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	return (new_array);
}

char	**add_line(char **old_array, size_t len, size_t del_index, int del_line_index)
{
	char	**new_array;
	int		i;

	new_array = allocate_2d_array(old_array);
	i = 0;
	if (del_line_index == 0)
	{
		new_array[i++] = ft_substr(old_array[i], 0, del_index);
		new_array[i] = ft_substr(old_array[i - 1], del_index + 1, ft_strlen(old_array[i-1]));
	}
	while (i < ft_arrlen(old_array))
	{
		if (i == del_line_index)
		{
			new_array[i] = ft_substr(old_array[i], 0, del_index);
			new_array[i+1] = ft_substr(old_array[i], del_index + 1, ft_strlen(old_array[i]));
		}
		else
			new_array[i] = ft_strdup(old_array[i]);
		i++;
	}
	ft_free_array(old_array);
	return (new_array);
}

char	**parse_line(char **array, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		arrlen;

	// printf("coming from main array[0]: %s\n", array[0]);
	i = 0;
	while (i < ft_arrlen(array))
	{
		j = 0;
		while (j < ft_strlen(array[i]))
		{
			if (is_delim(array[i][j]) == true)
			{
				// printf("found delim in array[%i] at index %i\n\n", i, j);
				arrlen = ft_arrlen(array);
				array = add_line(array, arrlen, j, i);
			}
			j++;
		}
		i++;
	}
	int u = 0;
	while (array[u])
	{
		printf("after add_line array[%u]: %s\n", u, array[u]);
		u++;
	}
}

char	**ft_lexer(char *str)
{
	char	*trimmed_str;
	char	**new_str;
	int		len;

	trimmed_str = ft_strtrim(str, " \t");
	len = ft_strlen(trimmed_str);
	new_str = (char **)ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (0);
	new_str[0] = ft_strdup(trimmed_str);
	parse_line(new_str, len);
}
