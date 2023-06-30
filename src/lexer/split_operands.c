/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:16:07 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/30 11:54:06 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

static bool	is_operand(int *operands, char c)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (operands[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static bool	over_one_op(char *str, int i)
{
	if (str[i] == str[i - 1])
		return (true);
	else
		return (false);
}

static void	count_op(char const *str, t_lexer *lexer, int len)
{
	int	i;

	i = 0;
	if (str[i] != 34 && str[i] != 39)
	{
		// printf("str[i]: %c\n", str[i]);
		while (i < len)
		{
			if (str[i] == 62 || str[i] == 60 || str[i] == 124)
			{
				if (over_one_op(str, i) == false)
					lexer->op_count++;
			}
			i++;
		}
		// printf("lexer->op_count: %i\n", lexer->op_count);
	}
}
// static int	set_string(char *split_array_op, char *split_array_de, int k, t_lexer *lexer)
// {
// 	int	start;

// 	start = k;
// 	// printf("k in set string = %i\n", k);
// 	// printf("start in set string = %i\n", start);
// 	if (is_operand(lexer->operands, split_array_de[k]) == true)
// 	{
// 		if (is_operand(lexer->operands, split_array_de[k + 1]) == true)
// 			k += 2;
// 		else
// 			k += 1;
// 	}
// 	else if (is_operand(lexer->operands, split_array_de[k]) == false)
// 	{
// 		while (is_operand(lexer->operands, split_array_de[k]) == false)
// 			k++;
// 	}
// 	split_array_op = ft_calloc((k - start + 1), sizeof(char *));
// 	if (!split_array_op)
// 		return (0);
// 	ft_strlcpy(split_array_op, &split_array_de[start], (k - start + 1));
// 	printf("split_array_op after strlcpy:%s\n", split_array_op);

// 	printf("returning k: %i\n", k);
// 	return (k);
// }

void	**put_array_op(char **split_array_op, char **split_array_de, t_lexer *lexer)
{
	int i;
	int j;
	int k;
	int start;

	i = 0;
	j = 0;
	k = 0;
	start = 0;
	if (split_array_de[i][j] == 34 || split_array_de[i][j] == 39)
	{
		printf("HERE\n");
		split_array_op[k] = ft_strdup(split_array_de);
		k++;
		i++;
	}
	while (k < lexer->op_count + lexer->token_count)
	{
		while (j < ft_strlen(split_array_de[i]))
		{
			if (is_operand(lexer->operands, split_array_de[i][j]) == true)
			{
				split_array_op[k] = ft_substr(split_array_de[i], start, j);
				printf("plit_array_op[%i]: %s\n", k, split_array_op[i]);
			}
			start = j;
			j++;
		}
	k++;
	}
}
/*
1) if first is quote
2) if op found
3)if op not found
*/

// void		search_op(char *split_array_de, t_lexer *lexer)
// {

// }

char	**split_op(char **split_array_op, char **split_array_de, t_lexer *lexer)
{
	int	i;

	i = 0;
	while (i < lexer->token_count)//loop strings
	{
		count_op(split_array_de[i], lexer, ft_strlen(split_array_de[i]));
		i++;
	}
	// printf("lexer->op_count: %i\n", lexer->op_count);
	if (lexer->op_count == 0)
		return (split_array_de);
	else
	{
		split_array_op = ft_calloc((lexer->op_count + lexer->token_count + 1), sizeof(char *));
		if (!split_array_op)
			return (NULL);
		split_array_op = put_array_op(split_array_op, split_array_de, lexer); // this not working
		i = 0;
		// while (i < lexer->op_count + lexer->token_count)
		// {
		// 	printf("plit_array_op[%i]: %s\n", i, split_array_op[i]);
		// 	i++;
		// }
		return (split_array_op);
	}
}

// void	**put_array_op(char **split_array_op, char **split_array_de, t_lexer *lexer)
// {
// 	int	i; // loops split_array_op
// 	int	j; // loops split_array_de
// 	int	k; // goes trough split_array_de[j] indexes

// 	i = 0;
// 	j = 0;
// 	while (i < lexer->token_count + lexer->op_count)
// 	{
// 		k = 0;
// 		while (k < ft_strlen(split_array_de[j]))
// 		{
// 			k += set_string(split_array_op[i], split_array_de[j], k, lexer);
// 			printf("split array op in put array: %s\n", split_array_op[i]);
// 			i++;
// 		}
// 		j++;
// 	}
// 	i = 0;
// 	while (i < lexer->op_count + lexer->token_count)
// 	{
// 		printf("split_array_op[%i]: %s\n", i, split_array_op[i]);
// 		i++;
// 	}
// }
