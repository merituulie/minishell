/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_delims.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:12:16 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/30 10:50:58 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

static bool	is_delim(int *delims, char c)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (delims[i] == c)
			return (true);
		i++;
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

void	count_tokens_de(char const *str, t_lexer *lexer, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == 34)
			lexer->dq_flag = !lexer->dq_flag;
		if (str[i] == 39)
			lexer->sq_flag = !lexer->sq_flag;
		else if ((is_delim(lexer->delims, str[i]) == true \
			&& is_delim(lexer->delims, str[i - 1]) == false) \
			&& is_same_quote(lexer->dq_flag, lexer->sq_flag) == true)
			lexer->token_count++;
		i++;
	}
	if (str[i] == '\0' && is_delim(lexer->delims, str[i - 1]) == false)
		lexer->token_count++;
}

char	**put_array_de(char **array, char *str, t_lexer *lexer)
{
	int	start;
	int	i;
	int	j;

	start = 0;
	i = 0;
	j = 0;
	while (j < lexer->token_count && str[i] != '\0')
	{
		if (str[i] == 34)
			lexer->dq_flag = !lexer->dq_flag;
		if (str[i] == 39)
			lexer->sq_flag = !lexer->sq_flag;
		else if ((is_delim(lexer->delims, str[i]) == true \
			&& is_delim(lexer->delims, str[i - 1]) == false) \
			&& is_same_quote(lexer->dq_flag, lexer->sq_flag) == true)
		{
			array[j] = ft_substr(str, start, (i - start + 1));
			start = i + 1;
			j++;
		}
		i++;
	}
	if (str[i] == '\0')
		array[j] = ft_substr(str, start, (i - start + 1));
	return (array);
}

char **split_de(char *str, t_lexer *lexer)
{
	char	**put_array;
	char	**split_array_de;
	int		i;

	count_tokens_de(str, lexer, ft_strlen(str));
	put_array = ft_calloc(lexer->token_count + 1, sizeof(char *));
	if (!put_array)
		return (-1);
	put_array = put_array_de(put_array, str, lexer);
	free (str);
	split_array_de = ft_calloc(lexer->token_count + 1, sizeof(char *));
	if (!split_array_de)
		return (-1);
	i = 0;
	while (i < lexer->token_count)
	{
		split_array_de[i] = ft_strtrim(put_array[i], lexer->delims, 4);
		i++;
	}
	ft_free_array(put_array);
	return (split_array_de);
}

