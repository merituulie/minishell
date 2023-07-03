/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/03 18:07:51 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

size_t	ft_arrlen(const char **array)
{
	size_t	counter;

	counter = 0;
	while (array[counter] != '\0')
	{
		counter++;
	}
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

void trim_last_line(char **array)
{
	size_t	arr_len;

	arr_len = ft_arrlen(array);
	if (arr_len > 0)
	{
		char *trimmed_last_line = ft_strtrim(array[arr_len - 1], " \t\n");
		if (trimmed_last_line)
		{
			free(array[arr_len - 1]);
			array[arr_len - 1] = trimmed_last_line;
		}
	}
}

char	**add_line(char **old_array, size_t len, size_t del_index, int del_line_index)
{
	char	**new_array;
	int		i;

	new_array = allocate_2d_array(old_array);
	i = 0;
	if (del_line_index == 0)
	{
		new_array[i] = ft_substr(old_array[i], 0, del_index);
		i++;
		new_array[i] = ft_substr(old_array[i - 1], del_index, ft_strlen(old_array[i-1]));
	}
	while (i < ft_arrlen(old_array) && old_array[i])
	{
		if (i == del_line_index)
		{
			new_array[i] = ft_substr(old_array[i], 0, del_index);
			new_array[i+1] = ft_substr(old_array[i], del_index, ft_strlen(old_array[i]));
		}
		else
			new_array[i] = ft_strdup(old_array[i]);
		i++;
	}
	return (new_array);
}

char	**parse_line(char **array, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		arrlen;
	char		**new_array;

	i = 0;
	while (i < ft_arrlen(array))
	{
		j = 0;
		while (j < ft_strlen(array[i]))
		{
			if (is_delim(array[i][j]) == true)
			{
				arrlen = ft_arrlen(array);
				new_array = add_line(array, arrlen, j, i);
				ft_free_array(array);
				array = (char **)ft_calloc(arrlen + 2, sizeof(char *));
				if (!array)
					return (NULL);
				for (size_t k = 0; k < arrlen + 1; k++)
				{
					array[k] = ft_strdup(new_array[k]);
					if (!array[k])
						return (NULL);
				}
				ft_free_array(new_array);
				if (is_delim(array[i + 1][0]) == true)
					trim_last_line(array);
				break;
			}
			j++;
		}
		i++;
	}
	//
		int u = 0;
		while (array[u])
		{
			printf("after add_line array[%u]: %s\tp: %p\n", u, array[u], &(*array[u]));
			u++;
		}
	//
	return(array);
}

char	**ft_lexer(char *str)
{
	char	*trimmed_str;
	char	**new_str;
	char	**parsed_line;
	int		len;

	trimmed_str = ft_strtrim(str, " \t");
	len = ft_strlen(trimmed_str);
	printf("***********len == %i\n", len);
	new_str = (char **)ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (0);
	new_str[0] = ft_strdup(trimmed_str);
	if (trimmed_str)
		free(trimmed_str);
	parsed_line = parse_line(new_str, len);
	return (parsed_line);
}
