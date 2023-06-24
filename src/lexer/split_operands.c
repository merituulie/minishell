/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:16:07 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/24 10:00:00 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

// static bool	is_delim(int *delims, char c)
// {
// 	while (*delims != '\0')
// 	{
// 		if (*delims == c)
// 			return (true);
// 		delims++;
// 	}
// 	return (false);
// }

// static bool	is_same_quote(int d_quote_flag, int s_quote_flag)
// {
// 	if (d_quote_flag == 0 && s_quote_flag == 0)
// 		return (true);
// 	else
// 		return (false);
// }

void	count_op(char const *str, t_lexer *lexer, int len)
{
	int	i;

	i = 0;
	if (str[i] == 62 || str[i] == 60)
	{
		lexer->op_count ++;
		if (str[i + 1] == 62 || str[i + 1] == 60)
			lexer->op_count ++;
	}
	if (str[len - 1] == 62 || str[len - 1] == 60)
	{
		lexer->op_count ++;
		if (str[len - 2] == 62 || str[len -2] == 60)
			lexer->op_count ++;
	}
}

// char	**put_array_op(char **token_array, char *str, t_lexer *lexer)
// {
// 	int	start;
// 	int	i;
// 	int	j;

// 	lexer->dq_flag = 0;
// 	lexer->sq_flag = 0;
// 	start = 0;
// 	i = 0;
// 	j = 0;
// 	while (j < lexer->token_count && str[i] != '\0')
// 	{
// 		if (str[i] == 34)
// 			lexer->dq_flag = !lexer->dq_flag;
// 		if (str[i] == 39)
// 			lexer->sq_flag = !lexer->sq_flag;
// 		else if ((is_delim(lexer->delims, str[i]) == true \
// 			&& is_delim(lexer->delims, str[i - 1]) == false) \
// 			&& is_same_quote(lexer->dq_flag, lexer->sq_flag) == true)
// 		{
// 			token_array[j] = ft_calloc((i - start + 1), sizeof(char *));
// 			if (!token_array[j])
// 				return (0);
// 			ft_strlcpy(token_array[j], &str[start], (i - start + 1));
// 			start = i + 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (str[i] == '\0')
// 	{
// 		token_array[j] = ft_calloc((i - start + 1), sizeof(char *));
// 		if (!token_array[j])
// 			return (0);
// 		ft_strlcpy(token_array[j], &str[start], (i - start + 1));
// 	}
// }

char	**split_op(char **token_array, t_lexer *lexer)
{
	int	i;
	char **separate_op;

	i = 0;
	while (i < lexer->token_count)
	{
		count_op(token_array[i], lexer, ft_strlen(token_array[i]));
		i++;
	}
	printf("op count:%i\n", lexer->op_count);
	separate_op = ft_calloc((lexer->op_count + lexer->token_count), sizeof(char *));
	// separate_op = put_array_op(separate_op, token_array, lexer);
	return (separate_op);
}
