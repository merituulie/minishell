/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/04 17:04:45 by yoonslee         ###   ########.fr       */
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

void **trim_last_line(char **array, int line_index)
{
	size_t	arr_len;
	char	*new_last_line;

	new_last_line = ft_strtrim(array[line_index], " \t\n");
	free(array[line_index]);
	array[line_index] = new_last_line;
}

char	**add_line(char **old_array, size_t len, size_t del_index, int del_line_index)
{
	char	**new_array;
	int		i;

	printf("\n----------addline function starts-----------\n");
	printf("del_line_index: %d\n", del_line_index);
	printf("del_index: %d\n", del_index);
	new_array = allocate_2d_array(old_array);
	i = 0;
	if (del_line_index == 0)
	{
		new_array[0] = ft_substr(old_array[0], 0, del_index);
		printf("old_array[0] is %s\n", old_array[0]);
		printf("length is %d\n", ft_strlen(old_array[0]) - del_index);
		new_array[1] = ft_substr(old_array[0], del_index, (ft_strlen(old_array[0]) - del_index));
		printf("new_array[1] is %s\n", new_array[1]);
	}
	else
	{
		while (i < ft_arrlen(old_array))
		{
			if (i == del_line_index)
			{
				new_array[i] = ft_substr(old_array[i], 0, del_index);
				printf("new_array[%d] is %s\n", i, new_array[i]);
				new_array[i+1] = ft_substr(old_array[i], del_index + 1, ft_strlen(old_array[i]));
				printf("new_array[%d] is %s\n", i, new_array[i]);
			}
			else
			{
				new_array[i] = ft_strdup(old_array[i]);
				printf("new_array[%d] is %s\n", i, new_array[i]);
			}
			i++;
		}
	}
	ft_free_array(old_array);
	printf("\n----------addline function ends-----------\n");
	return (new_array);
}

char	**parse_line(char **array, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		arrlen;
	char		*out;
	char		*new_last_line;

	i = 0;
	printf("\n-------parse_line function starts---------\n");
	while (i < ft_arrlen(array))
	{
		j = 0;
		while (j < ft_strlen(array[i]))
		{
			if (is_delim(array[i][j]) == true)
			{
				printf("found delim in array[%i] at index %i\n", i, j);
				arrlen = ft_arrlen(array);
				printf("arrlen: %d\n", arrlen);
				printf("i : %d\n", i);
				array = add_line(array, arrlen, j, i);
				if (is_delim(array[i + 1][0]) == true)
					trim_last_line(array, i + 1);
			}
			j++;
		}
		i++;
	}
	printf("\n--------parse_line function ends---------\n");
	return (array);
}

char	**ft_lexer(char *str)
{
	char	*trimmed_str;
	char	**new_str;
	char	**parsed_line;
	int		len;
	int	i = -1;

	printf("\n--------ft_lexer function starts---------\n");
	trimmed_str = ft_strtrim(str, " \t");
	len = ft_strlen(trimmed_str);
	printf("trimmed string len: %i\n", len);
	new_str = (char **)ft_calloc(2, sizeof(char *));
	if (!new_str)
		return (0);
	new_str[0] = ft_strdup(trimmed_str);
	free(trimmed_str);
	parsed_line = parse_line(new_str, len);//parsed_line needs to be malloced to get new_str
	printf("\n--------back to ft_lexer func------------\n");
	while (parsed_line[++i])
		printf("parsed_line is %s\n", parsed_line[i]);
	printf("\n--------ft_lexer function ends---------\n");
	return (parsed_line);
}
