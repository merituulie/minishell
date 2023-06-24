/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_delims.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:12:16 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/24 18:31:10 by jhusso           ###   ########.fr       */
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
		// printf("delim = %i\n", delims[i]);
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
		// printf("str[%i] = %c\n", i, str[i]);
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
	printf("token count: %i\n", lexer->token_count);
}

char	**split_de(char **array, char *str, t_lexer *lexer)
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
			array[j] = ft_calloc((i - start + 1), sizeof(char *));
			if (!array[j])
				return (0);
			ft_strlcpy(array[j], &str[start], (i - start + 1));
			start = i + 1;
			// printf("# %s\n", array[j]);
			j++;
		}
		i++;
	}
	if (str[i] == '\0')
	{
		array[j] = ft_calloc((i - start + 1), sizeof(char *));
		if (!array[j])
			return (0);
		ft_strlcpy(array[j], &str[start], (i - start + 1));
		// printf("# %s\n", array[j]);
	}
	return (array);
}
