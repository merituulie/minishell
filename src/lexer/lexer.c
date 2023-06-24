/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/24 09:01:25 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

static bool	is_delim(int *delims, char c)
{
	while (*delims != '\0')
	{
		if (*delims == c)
			return (true);
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

static void	count_tokens(char const *str, t_lexer *lexer, int len)
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

char	**ft_trimcmd(char **token_array, char *str, t_lexer *lexer)
{
	int	start;
	int	i;
	int	j;

	lexer->dq_flag = 0;
	lexer->sq_flag = 0;
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
	t_lexer	lexer;
	char	*trimmed_line;
	char	**put_array;
	char	**trimmed_array;
	int		i;

	init_struct(&lexer, str);
	trimmed_line = ft_strtrim(str, lexer.delims);
	count_tokens(trimmed_line, &lexer, ft_strlen(trimmed_line));
	put_array = ft_calloc(lexer.token_count + 1, sizeof(char *));
	if (!put_array)
		return (-1);
	put_array = ft_trimcmd(put_array, trimmed_line, &lexer);
	free (trimmed_line);
	trimmed_array = ft_calloc(lexer.token_count + 1, sizeof(char *));
	if (!trimmed_array)
		return (-1);
	i = 0;
	while (i < lexer.token_count)
	{
		trimmed_array[i] = ft_strtrim(put_array[i], lexer.delims);
		printf("%s\n", trimmed_array[i]);
		i++;
	}
	ft_free_array(put_array);
	return (0);
}
