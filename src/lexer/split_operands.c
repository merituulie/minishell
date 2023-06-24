/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:16:07 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/24 18:35:18 by jhusso           ###   ########.fr       */
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
	while (i < len)
	{
		if (str[i] == 62 || str[i] == 60 || str[i] == 124)
		{
			if (over_one_op(str, i) == false)
				lexer->op_count++;
		}
		i++;
	}
}
static int	set_string(char *split_array_op, char *split_array_de, int k, t_lexer *lexer)
{
	int	start;

	start = 0;
	while (is_operand(lexer->operands, split_array_de[k]) == false)
		k++;
	if (is_operand(lexer->operands, split_array_de[k]) == true)
	{
		if (is_operand(lexer->operands, split_array_de[k + 1]) == true)
			k += 2;
	}
	split_array_op = ft_calloc((k - start + 1), sizeof(char *));
	if (!split_array_op)
		return (0);
	ft_strlcpy(split_array_op, split_array_de, (k - start));
	return (k);
}

char	**put_array_op(char **split_array_op, char **split_array_de, t_lexer *lexer)
{
	int	i; // loops split_array_op
	int	j; // loops split_array_de
	int	k; // goes trough split_array_de[j] indexes

	i = 0;
	j = 0;
	while (i < lexer->token_count + lexer->op_count)
	{
		k = 0;
		while (k < ft_strlen(split_array_de[j]))
		{
			set_string(split_array_op[i], split_array_de[j], k, lexer);
			i++;
		}
		i++;
		j++;
	}
	// if (str[i] == '\0')
	// {
	// 	split_array_de[j] = ft_calloc((i - start + 1), sizeof(char *));
	// 	if (!split_array_de[j])
	// 		return (0);
	// 	ft_strlcpy(split_array_de[j], &str[start], (i - start + 1));
	// }
}

char	**split_op(char **split_array_de, t_lexer *lexer)
{
	int	i;
	char **split_array_op;

	i = 0;
	while (i < lexer->token_count)
	{
		count_op(split_array_de[i], lexer, ft_strlen(split_array_de[i]));
		i++;
	}
	printf("op count:%i\n", lexer->op_count);
	split_array_op = ft_calloc((lexer->op_count + lexer->token_count), sizeof(char *));
	if (!split_array_op)
		return (NULL); // error
	split_array_op = put_array_op(split_array_op, split_array_de, lexer);
	return (split_array_op);
}
