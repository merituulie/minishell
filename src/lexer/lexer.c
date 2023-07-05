/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/05 14:23:46 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/*handling "" case??*/

size_t	ft_arrlen(const char **array)
{
	size_t	counter;

	counter = 0;
	while (*array != '\0')
	{
		counter++;
		array++;
	}
	return (counter);
}

bool	is_delim(char c)
{
	char *delims;

	delims = " \t\n<>|";
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

void **trim_last_line(char **array, int line_index)
{
	size_t	arr_len;
	char	*new_last_line;

	new_last_line = ft_strtrim(array[line_index], " \t\n");
	printf("new_last_line is %s\n", new_last_line);
	free(array[line_index]);
	array[line_index] = new_last_line;
	printf("array[%d] is %s\n", line_index, array[line_index]);
}

char	*special_case1(char *old_array, int i, int del_index)
{
	char	*out;

	if (del_index == 0)
		del_index = 1;
	printf("i is %d\n", i);
	printf("del_index is %d\n", del_index);
	out = ft_substr(old_array, i, del_index);
	printf("out in special case1 is: %s\n", out);
	printf("----------------------------------------\n");
	return (out);
}

char	*special_case2(char *old_array, int del_index, int len)
{
	char	*out;

	if (del_index == 0)
		del_index = 1;
	printf("del_index is %d\n", del_index);
	printf("len is %d\n", len);
	out = ft_substr(old_array, del_index, len);
	printf("out in special case2 is: %s\n", out);
	printf("----------------------------------------\n");
	return (out);
}

char	**add_line(char **old_array, size_t len, size_t del_index, int del_line_index)
{
	char	**new_array;
	int		i;

	new_array = allocate_2d_array(old_array);
	i = -1;
	if (del_line_index == 0)
	{
		printf("-------------del_line_index is %d------------------\n", del_line_index);
		new_array[0] = special_case1(old_array[0], 0, del_index);
		new_array[1] = special_case2(old_array[0], del_index, (ft_strlen(old_array[0]) - del_index));
	}
	else
	{
		printf("-------------del_line_index is %d------------------\n", del_line_index);
		while (++i < ft_arrlen(old_array))
		{
			if (i == del_line_index)
			{
				new_array[i] = special_case1(old_array[i], 0, del_index);
				new_array[i + 1] = special_case2(old_array[i], del_index + 1, ft_strlen(old_array[i]));
			}
			else
				new_array[i] = ft_strdup(old_array[i]);
		}
	}
	ft_free_array(old_array);
	return (new_array);
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
	// printf("ERROR\n");
	return (j);
}

int		double_redir(char *str, int j)
{
	if (str[j] != '<' && str[j] != '>')
		return (j);
	if (str[j] == '<' || str[j] == '>')
	{
		if (str[j] == str[j + 1])
			return (j + 1);
		else
			return (j);
	}
}

char	**parse_line(char **array, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		arrlen;

	i = 0;
	while (i < ft_arrlen(array) && array[i])
	{
		j = 0;
		while (j < ft_strlen(array[i]))
		{
			if (array[i][j] == 34 || array[i][j] == 39)
				j = quote_index(array[i], j);
			if (is_delim(array[i][j]) == true)
			{
				j = double_redir(array[i], j);
				printf("index j is: %d\n", j);
				arrlen = ft_arrlen(array);
				array = add_line(array, arrlen, j, i);
				if (is_delim(array[i + 1][0]) == true)
					trim_last_line(array, i + 1);
			}
			j++;
		}
		i++;
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
	printf("trimmed string len: %i\n", len);
	
	new_str = (char **)ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (0);
	new_str[0] = ft_strdup(trimmed_str);
	free(trimmed_str);
	parsed_line = parse_line(new_str, len);
	// int i = -1;
	// while (parsed_line[++i])
	// 	printf("parsed_line is %s\n", parsed_line[i]);
	return (parsed_line);
	// return (0);
}
