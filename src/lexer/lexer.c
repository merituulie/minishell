/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/22 15:28:18 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

static bool	is_delim(int *delims, char c)
{
	while (*delims != '\0')
	{
		if (*delims == c)
		{
			// printf("HERE *\n");
			return (true);
		}
		delims++;
	}
	return (false);
}

static bool	is_same_quote(int d_quote_flag, int s_quote_flag)
{
	if (d_quote_flag == 0 && s_quote_flag == 0)
		return (true);
	else
		return (false);
}

int	count_tokens(char const *str, int *delims, int len)
{
	int	token_count;
	int	d_quote_flag;
	int	s_quote_flag;
	int	i;

	token_count = 0;
	d_quote_flag = 0;
	s_quote_flag = 0;
	i = 0;
	if (!str)
		return (0);
	while (i < len)
	{
		if (str[i] == 34)
			d_quote_flag = !d_quote_flag;
		if (str[i] == 39)
			s_quote_flag = !s_quote_flag;
		else if ((is_delim(delims, str[i]) == true && is_delim(delims, str[i-1]) == false)\
			&& is_same_quote(d_quote_flag, s_quote_flag) == true)
			token_count++;
		i++;
	}
	if (str[i] == '\0' && is_delim(delims, str[i - 1]) == false)
		token_count++;

	return (token_count);
}

char	**ft_trimcmd(char **token_array, char *str, int *delims, \
		int token_count)
{
	int	d_quote_flag;
	int	s_quote_flag;
	int	start;
	int	i;
	int	j;

	d_quote_flag = 0;
	s_quote_flag = 0;
	start = 0;
	i = 0;
	j = 0;
	while (j < token_count && str[i] != '\0')
	{
		if (str[i] == 34)
			d_quote_flag = !d_quote_flag;
		if (str[i] == 39)
			s_quote_flag = !s_quote_flag;
		else if (is_delim(delims, str[i]) == true && is_delim(delims, str[i-1]) == false \
			&& is_same_quote(d_quote_flag, s_quote_flag) == true)
		{
			token_array[j] = ft_calloc((i - start + 1), sizeof(char *));
			if (!token_array[j])
				return (0);
			ft_strlcpy(token_array[j], &str[start], (i - start + 1));
			start = i + 1;
			j++;
		}
		i++;
	}
	if (str[i] == '\0')
	{
		token_array[j] = ft_calloc((i - start + 1), sizeof(char *));
		if (!token_array[j])
			return (0);
		ft_strlcpy(token_array[j], &str[start], (i - start + 1));
	}
}

char	**ft_lexer(char *str)
{
	int		delims[4];
	int		token_count;
	char	*trimmed_array;
	char	**trimcmd_array;
	int		i;

	init_set(delims);
	trimmed_array = ft_strtrim(str, delims);
	token_count = count_tokens(trimmed_array, delims, ft_strlen(trimmed_array));
	trimcmd_array = ft_calloc(token_count + 1, sizeof(char *));
	if (!trimcmd_array)
		return (-1);
	trimcmd_array = ft_trimcmd(trimcmd_array, trimmed_array, delims, token_count);
	i = 0;
	while (i < token_count)
	{
		trimcmd_array[i] = ft_strtrim(trimcmd_array[i], delims);
		printf("after trimmin: %s\n", trimcmd_array[i]);
		i++;
	}
	return (0);
}
